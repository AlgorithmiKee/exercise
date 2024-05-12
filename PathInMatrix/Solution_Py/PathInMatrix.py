from functools import cache
import time

NIL = -1


def f(X, n, m):
    global visual_stack
    visual_stack += '.'

    # unreachable point
    if X[n][m] == 0:
        re = 0
    else:
        if m==0 and n==0:
            re = 1
        elif m==0:
            re = f(X, n-1, m)
        elif n==0:
            re = f(X, n, m-1)
        else:
            re = f(X, n-1, m) + f(X, n, m-1)
    # print(f"{visual_stack} Y[{n}][{m}] = {re}")
    
    visual_stack = visual_stack[:-1]
    return re   

    
def fm(X, n, m, Y={}):
    global visual_stack
    visual_stack += '.'

    # update Y[n][m]
    if (n,m) not in Y:
        # unreachable point
        if X[n][m] == 0:
            Y[(n,m)] = 0
        else: 
            if m==0 and n==0:
                Y[(n,m)] = 1
            elif m==0:
                Y[(n,m)] = fm(X, n-1, m)
            elif n==0:
                Y[(n,m)] = fm(X, n, m-1)
            else:
                Y[(n,m)] = fm(X, n-1, m) + fm(X, n, m-1) 
        # print(f"{visual_stack} Y[{n}][{m}] = {Y[(n,m)]}")
    
    visual_stack = visual_stack[:-1]
    return Y[(n,m)]


X = [
    [1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1],
    [1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1],
    [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
    [1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1],
    [1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1],
    [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1],
    [1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1],
]

row, col = (15, 17)

def validate(f, X, row, col):
    global visual_stack
    visual_stack = ''

    start = time.time()
    result = f(X, row, col)
    end = time.time()
    duration_ms = (end - start)*1000
    return result, duration_ms

result_naiv, duration_naiv_ms = validate(f, X, row, col)
result_memo, duration_memo_ms = validate(fm, X, row, col)

print(f"Y[{row}][{col}] = {result_naiv}. Execution time: {duration_naiv_ms:.6f} ms")
print(f"Y[{row}][{col}] = {result_memo}. Execution time: {duration_memo_ms:.6f} ms")
