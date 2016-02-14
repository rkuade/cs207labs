import itertools
import os
import reprlib
from collections import defaultdict


class LightCurve:
    
    def __init__(self, data, metadict):
        self._time = [x[0] for x in data]
        self._amplitude = [x[1] for x in data]
        self._error = [x[2] for x in data]
        self.metadata = metadict
        self.filename = None

 #   @staticmethod    
#    def lc_reader(filename):
#        lclist=[]
#        lcdict={}
#        with open(filename) as fp:
#            lp = fp.readlines()
#            for i in range(len(lp)):
#                if i == 0:
#                    line1 = lp[i][1:]
#                if i == 1:
#                    line2 = lp[i][1:]
#                if lp[i].find('#')!=0:
#                    lclist.append([float(f) for f in lp[i].strip().split()])
#            for f in range(len(line1.strip().split())):
#                lcdict[line1.strip().split()[f]]=line2.strip().split()[f] 
#        return lclist,lcdict
        
    @classmethod
    def from_file(cls, filename):
        lclist, metadict = lc_reader(filename)
        instance = cls(lclist, metadict)
        instance.filename = filename
        return instance   

    def __repr__(self):
        class_name = type(self).__name__
        components = reprlib.repr(list(itertools.islice(self.timeseries,0,10)))
        components = components[components.find('['):]
        return '{}({})'.format(class_name, components)

    #your code here    
    def __len__(self):
        return len(self._time)
    
    def __getitem__(self, position):
        return (self._time[position],self._amplitude[position],self._error[position])
    
    @property    
    def time(self):
        return self._time
    
    @property
    def amplitude(self):
        return self._amplitude
    
    @property
    def timeseries(self):
        return zip(self._time,self._amplitude)

class LightCurveDB:
    
    def __init__(self):
        self._collection={}
        self._field_index=defaultdict(list)
        self._tile_index=defaultdict(list)
        self._color_index=defaultdict(list)
    
    def populate(self, folder):
        for root,dirs,files in os.walk(folder): # DEPTH 1 ONLY
            for file in files:
                if file.find('.mjd')!=-1:
                    the_path = root+"/"+file
                    self._collection[file] = LightCurve.from_file(the_path)
    
    def index(self):
        for f in self._collection:
            lc, tilestring, seq, color, _ = f.split('.')
            field = int(lc.split('_')[-1])
            tile = int(tilestring)
            self._field_index[field].append(self._collection[f])
            self._tile_index[tile].append(self._collection[f])
            self._color_index[color].append(self._collection[f])
     
    #your code here
    def retrieve(self, facet, value):
        facetdict = getattr(self,'_'+facet+'_index')
        return facetdict[value]

def lc_reader(filename):
    lclist=[]
    lcdict={}
    with open(filename) as fp:
        lp = fp.readlines()
        for i in range(len(lp)):
            if i == 0:
                line1 = lp[i][1:]
            if i == 1:
                line2 = lp[i][1:]
            if lp[i].find('#')!=0:
                lclist.append([float(f) for f in lp[i].strip().split()])
        for f in range(len(line1.strip().split())):
            lcdict[line1.strip().split()[f]]=line2.strip().split()[f] 
    return lclist,lcdict
 
