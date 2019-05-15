import os


input = os.popen("./../resources/generator --flow-one").read()
print(input)