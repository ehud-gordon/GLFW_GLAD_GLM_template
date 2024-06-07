python
import sys
sys.path.insert(0, '/home/ehud/gdb/eigen_gdb')  
from printers import register_eigen_printers
register_eigen_printers (None)
sys.path.insert(0, '/home/ehud/gdb/glm')
import glm_pp
end
