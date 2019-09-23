from ete3 import Tree

t = Tree('(A:0.1,B:0.2,(C:0.3,D:0.4):0.5);', format=1)
print(t.get_ascii(show_internal=True))