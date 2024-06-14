
from typing import List, Tuple
import re


def tokenize(expression) -> List[Tuple[str, str]]:
    # Define token patterns
    token_specification = [
        ('AND', r'&&'),      # AND operator
        ('OR', r'\|\|'),     # OR operator
        ('NOT', r'!'),       # NOT operator
        ('LPAREN', r'\('),   # Left Parenthesis
        ('RPAREN', r'\)'),   # Right Parenthesis
        ('VAR', r'[A-Za-z]+'),  # Variables
        ('SKIP', r'\s+'),    # Skip whitespace
        ('MISMATCH', r'.'),  # Any other character
    ]

    # Create the master regular expression
    token_regex = '|'.join(
        f'(?P<{pair[0]}>{pair[1]})' for pair in token_specification)

    # Tokenize the expression
    tokens = []
    for match in re.finditer(token_regex, expression):
        kind = match.lastgroup
        value = match.group()
        if kind == 'SKIP':
            continue
        elif kind == 'MISMATCH':
            raise ValueError(f'Unexpected character {value}')
        tokens.append((kind, value))

    return tokens


class Node:
    pass


class AndNode(Node):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __str__(self):
        return f'({self.left} && {self.right})'


class OrNode(Node):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __str__(self):
        return f'({self.left} || {self.right})'

class NotNode(Node):
    def __init__(self, operand):
        self.operand = operand

    def __str__(self):
        return f'!{self.operand}'

class VarNode(Node):
    def __init__(self, name):
        self.name = name

    def __str__(self):
        return self.name


def parse(tokens:List[Tuple[str,str]]) -> str:
    def parse_expression(index):
        left = parse_term(index)
        if index[0] < len(tokens) and tokens[index[0]][1] == '&&':
            index[0] += 1
            right = parse_expression(index)
            return AndNode(left, right)
        return left

    def parse_term(index):
        left = parse_factor(index)
        if index[0] < len(tokens) and tokens[index[0]][1] == '||':
            index[0] += 1
            right = parse_term(index)
            return OrNode(left, right)
        return left

    def parse_factor(index):
        if tokens[index[0]][1] == '(':
            index[0] += 1
            node = parse_expression(index)
            if tokens[index[0]][1] != ')':
                raise ValueError(f'Expected ) at position {index[0]}')
            index[0] += 1
            return node
        elif tokens[index[0]][1] == '!':
            index[0] += 1
            operand = parse_factor(index)
            return NotNode(operand)
        else:
            node = VarNode(tokens[index[0]][1])
            index[0] += 1
            return node

    index = [0]
    ast = parse_expression(index)
    return ast


def simplify(node: Node) -> Node:
    if isinstance(node, (AndNode, OrNode)):
        left = simplify(node.left)
        right = simplify(node.right)

        if isinstance(left, VarNode) and isinstance(right, VarNode):
            return node.__class__(left, right)
        elif isinstance(left, VarNode) and isinstance(right, NotNode) and isinstance(right.operand, VarNode):
            if left.name == right.operand.name:
                return node.__class__(left, right.operand)
        elif isinstance(left, NotNode) and isinstance(left.operand, VarNode) and isinstance(right, VarNode):
            if left.operand.name == right.name:
                return node.__class__(left.operand, right)
        elif isinstance(left, NotNode) and isinstance(right, NotNode) and isinstance(left.operand, VarNode) and isinstance(right.operand, VarNode):
            if left.operand.name == right.operand.name:
                return node.__class__(left.operand, right.operand)

    elif isinstance(node, NotNode):
        operand = simplify(node.operand)
        if isinstance(operand, VarNode):
            return NotNode(operand)

    return node


if __name__ == '__main__':
    exprs_to_simplify = [
        "a && b",
        "a && !b",
        "!a && b",
        "!a && !b",
    ]

    for expr in exprs_to_simplify:
        tokens = tokenize(expr)
        ast = parse(tokens)
        print(f'Original: {expr}')
        print(f'Simplified: {simplify(ast)}')
        print()