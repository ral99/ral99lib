#!/usr/bin/env python

import os
from argparse import ArgumentParser

def merge(modules, filename, extension):
    """
    Merge header and source files from modules and generate compressed header and source files with the specified extension in
    current directory.
    """
    # get header and source file paths
    header_files = []
    source_files = []
    for module in modules:
        module_files = [f for f in os.listdir(module) if os.path.isfile(os.path.join(module, f))]
        module_header_file = [f for f in module_files if f.endswith('.h')][0]
        module_source_file = [f for f in module_files if not f.endswith('.h') and not '_test' in f][0]
        header_files.append(os.path.join(module, module_header_file))
        source_files.append(os.path.join(module, module_source_file))

    # remove comments, merge includes and typedefs and write to a single header file
    header_includes = set([])
    header_typedefs = []
    header_lines = []
    for header_file in header_files:
        in_comment = False
        for line in open(header_file).readlines():
            if not in_comment:
                if line.lstrip().startswith('/*'):
                    if not line.rstrip().endswith('*/'):
                        in_comment = True
                    continue
                if line.lstrip().startswith('//'):
                    continue
                if line.lstrip().startswith('#include "'):
                    continue
                if line.lstrip().startswith('#include <'):
                    header_includes.add(line.strip())
                elif line.lstrip().startswith('typedef '):
                    header_typedefs.append(line.strip())
                elif not header_lines or line.strip() or header_lines[-1].strip():
                    header_lines.append(line)
            elif line.rstrip().endswith('*/'):
                in_comment = False
    merged_header = open('%s.%s' % (filename, 'h'), 'w')
    merged_header.write('#ifndef __%s__\n' % filename.upper())
    merged_header.write('#define __%s__\n\n' % filename.upper())
    for header_include in sorted(list(header_includes)):
        merged_header.write('%s\n' % header_include)
    merged_header.write('\n')
    for header_typedef in header_typedefs:
        merged_header.write('%s\n' % header_typedef)
    merged_header.write('\n')
    for header_line in header_lines:
        merged_header.write('%s' % header_line)
    merged_header.write('#endif\n')
    merged_header.close()

    # remove comments, merge includes and write to a single source file
    source_includes = set([])
    source_lines = []
    for source_file in source_files:
        in_comment = False
        for line in open(source_file).readlines():
            if not in_comment:
                if line.lstrip().startswith('/*'):
                    if not line.rstrip().endswith('*/'):
                        in_comment = True
                    continue
                if line.lstrip().startswith('//'):
                    continue
                if line.lstrip().startswith('#include "'):
                    continue
                if line.lstrip().startswith('#include <'):
                    source_includes.add(line.strip())
                elif not source_lines or line.strip() or source_lines[-1].strip():
                    source_lines.append(line)
            elif line.rstrip().endswith('*/'):
                in_comment = False
    merged_source = open('%s.%s' % (filename, extension), 'w')
    for source_include in sorted(list(source_includes)):
        merged_source.write('%s\n' % source_include)
    merged_source.write('\n#include "%s.h"\n' % filename)
    for source_line in source_lines:
        merged_source.write('%s' % source_line)
    merged_source.close()

def main():
    """
    Parse arguments and call merge function.
    """
    parser = ArgumentParser(description='Merge C and C++ modules from ral99lib.')
    parser.add_argument('modules', nargs='+', help='list of modules to be merged')
    parser.add_argument('filename', help='name of the merged header and source files.')
    parser.add_argument('extension', default='cpp', help='extension of the merged source file.')
    args = parser.parse_args()
    merge(args.modules, args.filename, args.extension)

if __name__ == '__main__':
    main()
