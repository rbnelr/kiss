import os
import re
from collections import namedtuple
import itertools
import shutil
import warnings

def delete_dir_contents(dir, del_subdirs=True):
	import os, shutil

	for the_file in os.listdir(dir):
		file_path = os.path.join(dir, the_file)
		try:
			if os.path.isfile(file_path):
				os.unlink(file_path)
			elif del_subdirs and os.path.isdir(file_path):
				shutil.rmtree(file_path)
		except Exception as e:
			print(e)

# set up output dir
dir = os.path.join('..', 'kiss_cpp', 'vector')

os.makedirs(dir, exist_ok=True)

delete_dir_contents(dir)

#
def delete_dir_contents(dir, del_subdirs=True):
	import os, shutil

	for the_file in os.listdir(dir):
		file_path = os.path.join(dir, the_file)
		try:
			if os.path.isfile(file_path):
				os.unlink(file_path)
			elif del_subdirs and os.path.isdir(file_path):
				shutil.rmtree(file_path)
		except Exception as e:
			print(e)

def format_indentation(text):
	lines = text.splitlines(1)

	indenters = ['{', '(', '[']
	dedenters = ['}', ')', ']']

	def set_indent(line, level):
		
		def unindent(line, indent_spaces=4):
			cur = 0
			def curc(): return line[cur] if cur < len(line) else 0

			def eat_tab():
				nonlocal cur

				spaces_eaten = 0
				while curc() == ' ':
					if spaces_eaten == indent_spaces:
						return True
					cur += 1
					spaces_eaten += 1
				
				if curc() == '\t':
					cur += 1
					return True

				return False

			while eat_tab():
				pass

			return line[cur:]

		line = unindent(line)

		lev = level
		if len(line) > 0 and line[0] in dedenters: # '}' should be on line of its corresponding open bracket
			lev = lev -1 if lev > 0 else 0

		return '\t'*lev + line # remove current indent and add desired indent

	def parse_indent_diff(line):
		diff = 0
		for c in line:
			if		c in indenters:	diff += 1
			elif	c in dedenters:	diff -= 1
		return diff

	indent_level = 0

	for i,l in enumerate(lines):
		line_level = indent_level

		indent_level += parse_indent_diff(l)

		lines[i] = set_indent(l, line_level)

	if indent_level != 0:
		warnings.warn('indent_level not 0, wrong brackets?')

	return ''.join(lines)

def generate(filename, generator):

	def write_file(filename, text):
		if text:
			text = format_indentation(text)
		
			with open(os.path.join(dir, filename), 'w') as f:
				f.write(text)
		else:
			try:
				os.remove(filename)
			except OSError:
				pass
	
	header = generator(header=True)
	source = generator(header=False)

	if header:
		header = f'''// generated by {__file__}
		#pragma once
	
		{header}
		'''
		
	if source:
		source = f'''// generated by {__file__}
		#include "{filename}.hpp"

		{source}
		'''
	
	write_file(f'{filename}.hpp', header)
	write_file(f'{filename}.cpp', source)
