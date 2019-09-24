'''
**************************************************************************
 File       [test.py]
 Author     [Orange Hsu]
 Synopsis   [Program for testing test cases]
**************************************************************************
'''

import os
import sys
import subprocess as sp

inputs_path = 'inputs/'
outputs_path = 'outputs/'
prog_path = 'bin/NTU_sort'

def main():
    if len(sys.argv) < 2:
        print('[ERROR] Missing option!')
        exit(-1)

    arg = sys.argv[1]
    print(arg)

    if (arg != '-IS' and arg != '-MS' and arg != '-QS' and arg != '-HS'):
        print('[ERROR] Invalid parameters!')
        exit(-1)

    print('Program for testing test cases')
    filenames = os.listdir(inputs_path)
    filenames.sort()
    
    for i in filenames:
        print('Testing file:' + i, flush=True)
    #    sp.call([prog_path, arg, inputs_path + i, outputs_path + i + '.out'])
    print('done.')

if __name__ == "__main__":
    main()