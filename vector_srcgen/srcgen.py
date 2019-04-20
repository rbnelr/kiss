import os
import re
from collections import namedtuple
import itertools
import shutil
import warnings

def format_indentation(text):
	lines = text.splitlines(1)

	indenters = ['{']
	aligners = ['(', '[']

	dedenters = ['}', ')', ']']
	
	indent_spaces = 4
	indent_amount = { '{':4 }

	indent_level = [0]
	in_assignment = False

	def unindent(line):
		cur = 0
		def curc(): return line[cur] if cur < len(line) else 0

		def eat_tab():
			nonlocal cur

			# spaces as indent mess with my alignment
			#spaces_eaten = 0
			#while curc() == ' ':
			#	if spaces_eaten == indent_spaces:
			#		return True
			#	cur += 1
			#	spaces_eaten += 1
				
			if curc() == '\t':
				cur += 1
				return True

			return False

		while eat_tab():
			pass

		return line[cur:]

	def indent(line, level):
		
		lev = level
		if len(line) > 0 and line[0] in dedenters: # '}' should be on line of its corresponding open bracket
			lev = indent_level[-1] if lev > 0 else 0

		tabs, spaces = divmod(lev, indent_spaces)

		return '\t'*tabs + ' '*spaces + line # remove current indent and add desired indent

	for line_i, line in enumerate(lines):
		line_level = indent_level[-1]

		line = unindent(line)
		
		def prevc():
			if (i-1) < 0:	return 0
			return line[i-1]
		def nextc():
			if (i+1) == len(line):	return 0
			return line[i+1]

		commented = False

		for i,c in enumerate(line):
			if c == '/' and nextc() == '/':
				commented = True
			if c == '\n':
				commented = False
			if commented:
				continue

			assignment = c == '=' and nextc() != '=' and \
				prevc() not in ['!','<','>','='] and not re.findall(r'operator\s*.=', line[:i+1])
			return_statement = i == 0 and line[:6] == 'return'

			if		c in indenters:
				indent_level.append(indent_level[-1] + indent_amount[c])

			elif	c in aligners or (assignment and not in_assignment) or return_statement:
				if return_statement:
					offs = i + 6 # skip 'return'
					indent_offs = 6
				else:
					offs = i + 1 # skip '='
					indent_offs = 1

				while (line[offs] in [' ', '\t']):
					indent_offs += indent_spaces if line[offs] == '\t' else 1
					offs += 1

				indent_level.append(line_level + i + indent_offs)

			elif	c in dedenters or (c == ';' and in_assignment):
				indent_level.pop()

			if assignment or return_statement:
				in_assignment = True
			if c == ';':
				in_assignment = False

		lines[line_i] = indent(line, line_level)

	if len(indent_level) != 1:
		warnings.warn('indent_level not 0, open closing tokes wrong?')

	return ''.join(lines)

class Generator:
	def __init__(self, output_dir, default_constexpr=False, default_inline=False):
		self.default_constexpr = default_constexpr
		self.default_inline = default_inline

		self.files = {}

		def delete_dir_contents(dir, del_subdirs=True):
			import os, shutil

			for the_file in os.listdir(self.dir):
				file_path = os.path.join(self.dir, the_file)
				try:
					if os.path.isfile(file_path):
						os.unlink(file_path)
					elif del_subdirs and os.path.isdir(file_path):
						shutil.rmtree(file_path)
				except Exception as e:
					print(e)

		self.dir = output_dir

		os.makedirs(self.dir, exist_ok=True)

		delete_dir_contents(self.dir)

	def add_file(self, *args):
		f = File(*args)

		f.default_constexpr = self.default_constexpr
		f.default_inline = self.default_inline

		self.files[f.name] = f
		return f
	
	def write_files(self):

		def write_file(filename, text, header):
			def line_has_code(l):
				l = l.strip()
				return len(l) > 0 and l[0] != '#' and l[:2] != '//'
			file_has_code = any(line_has_code(l) for l in text.splitlines())

			if file_has_code or header:
				text = format_indentation(text)
		
				with open(os.path.join(self.dir, filename), 'w') as f:
					f.write(text)
			else:
				try:
					os.remove(filename)
				except OSError:
					pass
		
		for f in self.files.values():
			if f.header:
				f.header = f'''// generated by {__file__}
				#pragma once
	
				{f.header}
				'''
		
			if f.source:
				f.source = f'''// generated by {__file__}
				#include "{f.name}.hpp"

				{f.source}
				'''
	
			write_file(f'{f.name}.hpp', f.header, header=True)
			write_file(f'{f.name}.cpp', f.source, header=False)

class File:
	def __init__(self, name):
		self.name = name
		self.header = ''
		self.source = ''

	def __add__(self, r):
		self.header += r
		self.source += r
		return self

	def _function(self, ret, name, args, body, clsname=None, init_list=None, template=None, forceinline=False, comment=None, const=False, static=False, explicit=False, constexpr='auto', inline='auto'):
		body = body.strip()
		comment = ''.join(f'// '+ l.strip() +'\n' for l in comment.splitlines()) if comment else ''

		# automaticly try to detect constexpr-ness by looking at the numer of lines in code body and function name blacklist (blacklisted functions call non-constexpr funcs like std lib sqrt())
		# this is what the c++ standard should have make the compiler do, instead of introducing another keyword that makes everyones live harder 
		non_constexpr_funcs = ['abs', 'sqrt', 'length', 'distance', 'normalize', 'normalize_or_zero', 'floor', 'floori', 'ceil', 'ceili', 'round', 'roundi', 'pow', 'wrap', 'min', 'max', 'clamp', 'bezier']
		if constexpr == 'auto':
			constexpr = self.default_constexpr and (init_list or body.count(';') == 1) and name not in non_constexpr_funcs
		if inline == 'auto':
			inline = self.default_inline

		clsname = f'{clsname}::' if clsname else ''
		init_list = f': {init_list}' if init_list else ''

		const = ' const' if const else ''
		
		declinline = None
		if forceinline:
			declinline = 'FORCEINLINE'
			inline = True
		#else:
		#	declinline = 'NOINLINE'
		#	inline = False

		static = 'static' if static else None
		constexpr = 'constexpr' if constexpr else None
		inline = 'inline' if inline else None
		explicit = 'explicit' if explicit else ''

		template = 'template<%s>\n' % template.replace('tn', 'typename') if template else ''

		_ctor_dtor = ret == ''

		callconv = None
		#if not _ctor_dtor:
		#	callconv = '__vectorcall'


		def spaced_join(*args):
			s = ''
			for a in args:
				if a:
					if s: s += ' '
					s += a
			return s

		defi_args = re.sub(r'=.*?(?=(?:,|$))', '', args) # argument list in func definition cannot have default argument values
		
		# header
		if inline or template:
			decl = template + spaced_join(static, inline, declinline, constexpr, explicit, ret, callconv, name)
			self.header += f'''\n{comment}{decl} ({args}){const}{init_list} {{
				{body}
			}}\n'''
		else:
			decl = spaced_join(static, declinline, constexpr, explicit, ret, callconv, name)
			self.header += f'{comment}{decl} ({args}){const};\n'

		# source
		if inline or template:
			pass # nothing
		else:
			decl = spaced_join(declinline, constexpr, ret, callconv, clsname + name)
			self.source += f'''\n{comment}{decl} ({defi_args}){const}{init_list} {{
				{body}
			}}\n'''

	def function(self, ret, name, args, body,										constexpr='auto', template=None, forceinline=False, comment=None):
		return self._function(str(ret), name, args, body,											constexpr=constexpr, template=template, forceinline=forceinline, comment=comment)
	def method(self, clsname, ret, name, args, body, explicit=False,				constexpr='auto', template=None, forceinline=False, comment=None, const=False):
		return self._function(str(ret), name, args, body, clsname=clsname, explicit=explicit,		constexpr=constexpr, template=template, forceinline=forceinline, comment=comment, const=const)
	def static_method(self, clsname, ret, name, args, body,							constexpr='auto', template=None, forceinline=False, comment=None, const=False):
		return self._function(str(ret), name, args, body, clsname=clsname,							constexpr=constexpr, template=template, forceinline=forceinline, comment=comment, const=const, static=True)
	def constructor(self, clsname, args, body='', init_list=None, explicit=False,	constexpr='auto', template=None, forceinline=False, comment=None):
		return self._function('', clsname, args, body, clsname=clsname, init_list=init_list, explicit=explicit,	constexpr=constexpr, template=template, forceinline=forceinline, comment=comment)

