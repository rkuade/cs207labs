import timeseries as ts
import lazy

def add(a,b):
    return a+b
def mul(a,b):
    return a*b
class LazyOperation():
    def __init__(self,function,*args,**kwargs):
        self.function = function
        self.args = *args
        self.kwargs = **kwargs

def lazy(f):
    return LazyOperation

@lazy
def lazy_add(a,b):
    return a+b

