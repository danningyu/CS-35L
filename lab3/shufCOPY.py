#!/usr/bin/env python3
import random, sys, argparse, string

"""
Output lines selected randomly from a file
For Python 3.

Danning Yu
305087992
"""

low_val = None #int, lower value
high_val = None #int, high value
print_amt_readin = -1
repeat_lines = False #can lines be repeated
read_from_stdin = True #read from stdin or not
input_range_option = False #lines come from lo to hi, inclusive
to_shuffle_contents = "" #string separated by newlines

def extract_number(alphanum):
  number_string=""
  for char in alphanum:
    if(char.isdigit()):
      number_string = number_string + char
    else:
      break
  return int(number_string)

def create_shuffled(to_shuffle_contents):
  to_shuffle_list = to_shuffle_contents.split("\n") #convert to list
  input_range_amount = len(to_shuffle_list)
  print_amt = print_amt_readin
  if input_range_amount < print_amt_readin \
   or (print_amt_readin == -1 and repeat_lines == False):
  #if less or not provided, only print the amount you have have
    print_amt = input_range_amount
  if repeat_lines == False:
    shuffled_list = random.sample(to_shuffle_list, print_amt)
    #random.sample() takes it without replacement
    for item in shuffled_list:
      print(item)
  elif repeat_lines == True:
    if print_amt_readin != -1:
      for i in range(0, print_amt_readin):
       print(random.choice(to_shuffle_list))
    elif print_amt_readin == -1:
      while True:
        print(random.choice(to_shuffle_list))

parser = argparse.ArgumentParser()
parser.add_argument("-i", "--input-range", action="store", dest="input_range",
                    help="treat each number in INPUT_RANGE as an input line")
parser.add_argument("-n", "--head-count", action="store", 
  dest="output_count", help="output at most OUTPUT_COUNT lines")
#read in value until first nondigit char
parser.add_argument("-r", "--repeat", action="store_true", default=False,
                    help="output lines can be repeated")
parser.add_argument("FILE", nargs='?', 
  help="With no FILE, or when FILE is -, read standard input.")

try:
  args = parser.parse_args()
except:
  sys.exit(1)

file_name = args.FILE
repeat_lines = args.repeat

if args.input_range: #-i or --input-range
  try:
  	dash_index = args.input_range.index('-')
  except:
  	print("shuf: invalid inptut range: " + args.input_range)
  	sys.exit(1)

  read_from_stdin = False
  input_range_option = True
  # first occurence of -
  try:
    low_val = int(args.input_range[0:dash_index])
    high_val = int(args.input_range[dash_index+1:])
    if(low_val > high_val):
      print("shuf: invalid input range: " + args.input_range)
      sys.exit(1)
    for i in range(low_val, high_val+1):
      to_shuffle_contents += (str(i)+"\n")
    to_shuffle_contents = to_shuffle_contents[:-1]
  except:
    print("shuf: invalid input range")
    sys.exit(1)

if args.output_count: #-n or --head-count
  try:
    print_amt_readin = extract_number(args.output_count)
  except:
    print("shuf: invalid line count: " + args.output_count)
    sys.exit(1)

if args.FILE:
  if input_range_option:
    print("shuf: extra operand " + args.FILE)
    print("Try 'shuf --help' for more information.")
    sys.exit(1)
  if args.FILE == "-":
    read_from_stdin = True
  else:
    try:
      text_file = open(args.FILE, "r")
      to_shuffle_contents = text_file.read()
      to_shuffle_contents = to_shuffle_contents[:-1]
      read_from_stdin = False #no longer need to read
    except:
      print("shuf: " + args.FILE + ": No such file or directory")
      sys.exit(1)

if read_from_stdin:
  to_shuffle_contents = sys.stdin.read() 
  # += not needed because read() gobbles up everything
  to_shuffle_contents = to_shuffle_contents[:-1] #remove \n at end

create_shuffled(to_shuffle_contents)

### Unit tests ###
def test_extract_number():
  extract_number("123")
  extract_number("12f")
  extract_number("f")
  extract_number("f1")
# test_extract_number()
