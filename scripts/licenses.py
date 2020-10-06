#!/usr/bin/env python3

import argparse
import io
import subprocess
import sys
import threading
import traceback

from concurrent.futures import ThreadPoolExecutor as Executor

parser = argparse.ArgumentParser()
parser.add_argument('agents', nargs='+')
args = parser.parse_args()

sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding='utf-8')

lock = threading.Lock()

def run(file, agent):
    completed = subprocess.run(['sh', agent + '.sh', file], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    with lock: [print('{}\t{}\t{}'.format(file, agent, license)) for license in completed.stdout.decode().splitlines()]

def execute(line):
    file = line.rstrip('\n')
    try: [run(file, agent) for agent in args.agents]
    except: traceback.print_exc()

with Executor() as executor: executor.map(execute, sys.stdin)
