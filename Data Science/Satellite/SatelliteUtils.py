import os
import earthpy.plot as ep
import tarfile

def get_earth_explorer_username():
    return os.environ['earth_explorer_username']

def get_earth_explorer_password():
    return os.environ['earth_explorer_password']

def plot_map(ds, indexes=[0,1,2], stretch=True):
    ep.plot_rgb(ds.ReadAsArray(), rgb=indexes, stretch=stretch)

def plot_bands(ds):
    ep.plot_bands(ds)

def untar(in_path, out_path):
    if not os.path.exists(out_path):
        os.makedirs(out_path)
    with tarfile.open(in_path) as tar:
        def is_within_directory(directory, target):
            
            abs_directory = os.path.abspath(directory)
            abs_target = os.path.abspath(target)
        
            prefix = os.path.commonprefix([abs_directory, abs_target])
            
            return prefix == abs_directory
        
        def safe_extract(tar, path=".", members=None, *, numeric_owner=False):
        
            for member in tar.getmembers():
                member_path = os.path.join(path, member.name)
                if not is_within_directory(path, member_path):
                    raise Exception("Attempted Path Traversal in Tar File")
        
            tar.extractall(path, members, numeric_owner=numeric_owner) 
            
        
        safe_extract(tar, out_path)