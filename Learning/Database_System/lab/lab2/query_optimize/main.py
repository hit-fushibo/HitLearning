query0 = 'SELECT [ ENAME = ’Mary’ & DNAME = ’Research’ ] ( EMPLOYEE JOIN DEPARTMENT )'
query1 = 'PROJECTION [ BDATE ] ( SELECT [ ENAME = ’John’ & DNAME = ’ Research’ ] ( EMPLOYEE JOIN DEPARTMENT ) )'
query2 = 'SELECT [ ESSN = ’01’ ] ( PROJECTION [ ESSN, PNAME ] ( WORKS_ON JOIN PROJECT ) )'
queries = [query0, query1, query2]


class Tree:
    def __init__(self, op='', info=''):
        self.child = []
        self.op = op
        self.info = info

    def __str__(self):
        return (self.op if self.op else '') + (' ' + self.info if self.info else '')


def Create_tree(query: str):
    elements, i, root = query.split(), 0, Tree()
    while i < len(elements):
        element = elements[i]
        if element == 'SELECT' or element == 'PROJECTION':
            end = elements.index(']', i)
            root.op, root.info = element, ' '.join(elements[i + 2:end])
            i = end + 1
        elif element == 'JOIN':
            root.op = element
            root.child.append(Tree(info=elements[i - 1]))  
            root.child.append(Tree(info=elements[i + 1]))  
            i += 1
        elif element == '(':
            count, idy = 1, i + 1
            while idy < len(elements) and count > 0:
                if elements[idy] == '(':
                    count += 1
                elif elements[idy] == ')':
                    count -= 1
                idy += 1
            root.child.append(Create_tree(' '.join(elements[i + 1:idy - 1])))
            i = idy
        else:
            i += 1
    return root


def Output_tree(root: Tree, sep=''):
    print(sep + str(root))
    if len(root.child) >= 1:
        Output_tree(root.child[0], sep + '\t')
    if len(root.child) >= 2:
        Output_tree(root.child[1], sep + '\t')


def Query_Optimize(root: Tree, info_lst=None):
    if root.op == 'SELECT':
        root = Query_Optimize(root.child[0], root.info.split('&')) # type: ignore
    elif root.op == 'PROJECTION':
        root.child[0] = Query_Optimize(root.child[0], info_lst)
    elif root.op == 'JOIN':
        if not info_lst:return
        node0 = Tree(op='SELECT', info=info_lst[0])
        node0.child.append(root.child[0])
        root.child[0] = node0
        if len(info_lst) > 1:
            node1 = Tree(op='SELECT', info=info_lst[1])
            node1.child.append(root.child[1])
            root.child[1] = node1
    return root


if __name__ == '__main__':
    for query_ in queries:
        print('************************************************************')
        print(query_)
        print('-------------')
        print('未优化')
        root1=Create_tree(query_)
        Output_tree(root1)
        root2=Query_Optimize(root1)
        print('-------------')
        print('优化')
        Output_tree(root2) # type: ignore
        

