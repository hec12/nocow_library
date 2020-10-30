#!/usr/bin/env python
import os
import glob
import logging

logging.basicConfig(format='%(asctime)s %(message)s',filename='./LibraryUpdate.log',level=logging.DEBUG)

def cpp2_snippet(filename,src_dir,dest_dir):

	file_input=open(src_dir,'r')
	file_output=open(dest_dir+filename+'.sublime-snippet','w')

	file_output.write('<snippet>\n')
	file_output.write('	<content><![CDATA[\n')


	for line in file_input:
		file_output.write(line.replace('$','\$'))

	file_output.write(']]></content>\n')
	file_output.write('<tabTrigger>'+filename+'</tabTrigger>\n')
	file_output.write('<scope>source.c++</scope>\n')
	file_output.write('</snippet>\n')


if __name__ == '__main__':
	src_dir='./src/'
	dest_dir='./snippet/'

	logging.info('Snippets are updated.')
	for root, dirs, files in os.walk(src_dir):
		for file in files:
			[filename,extention]=file.split('.')
			full_path=os.path.join(root,file)
			if filename.isupper() and extention == 'cpp':
				#print(full_path)
				cpp2_snippet(filename,full_path,dest_dir)
	#for filename in glob.glob('./src/geometry/*.cpp'):
	#	[target,extention]=filename.split('.')
	#	if extention == 'cpp':
	#		print(target,extention)	
