import sys

filename = sys.argv[1]
target = int(sys.argv[2])
count = 0

with open(filename) as f:
    for line in f:
        if line.find(".") == -1 and line.find(":") == -1 and line.find('#') == -1:
            count += 1

if (count > target):
    print(f"Counted {count} statements")
    exit(1)
    
exit (0)

