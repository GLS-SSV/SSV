# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#  This file is part of Space Shuttle Vessel
#
#  Mesh Tool Box
#
#
#
#  Space Shuttle Vessel is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  Space Shuttle Vessel is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with Space Shuttle Vessel; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
#  file SSV-LICENSE.txt for more details.
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
# # # # # SSV File Modification Notice  # # # #
# Date         Developer
# 2020/05/10   GLS
# 2020/06/02   GLS
# 2020/09/07   GLS
# 2021/08/11   GLS
# 2021/10/23   GLS
# 2021/12/19   GLS
# # # # # # # # # # # # # # # # # # # # # # # #

#  This file is part of Space Shuttle Ultra
#
#  Mesh Group Re-Order script
#
#
#
#  Space Shuttle Ultra is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  Space Shuttle Ultra is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with Space Shuttle Ultra; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#  See https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html or
#  file Doc\Space Shuttle Ultra\GPL.txt for more details.


import functools
import sys
import array
from dataclasses import dataclass



# mesh group struct
@dataclass
class MeshGroup:
    label: str
    material: int
    texture: int
    flag: int
    nonormal: bool
    texwrap: str
    zbias: int
    static: bool
    dynamic: bool
    geom_v: int
    geom_t: int
    vertices_x: array.array('d')
    vertices_y: array.array('d')
    vertices_z: array.array('d')
    vertices_nx: array.array('d')
    vertices_ny: array.array('d')
    vertices_nz: array.array('d')
    vertices_u: array.array('d')
    vertices_v: array.array('d')
    vertices_nouv: bool
    triangles: str

# mesh struct
@dataclass
class Mesh:
    staticmesh: bool
    grpcount: int
    grp: []
    matcount: int
    texcount: int
    mat: str
    tex: str


def printhelp():
    print( "SSV MTB Arguments:" )
    print( "-i<filename>\tInput file (mandatory)" )
    print( "-o<filename>\tOutput file (mandatory)" )
    print( "-f\t\tReorder groups for render performance" )
    print( "-u\t\tRemove UV coordinates on groups that use no texture (TEXTURE 0)" )
    print( "-z\t\tFix negative 0s" )
    print( "-h\t\tShow help (if present, only this screen will show)" )


def cleanline( line ):
    """strips comments and new line"""
    tmp1 = line.split( ";" )
    tmp2 = tmp1[0].rstrip()
    return tmp2


def reorder_mesh_groups( mesh ):
    """re-order mesh groups to minimize texture and material swaps"""
    mesh.grp = sorted( mesh.grp, key=functools.cmp_to_key( group_compare ) )
    return mesh


def eraseUV( mesh ):
    for x in mesh.grp:
        if x.texture == 0:
           if x.vertices_nouv == False:
               print( "Erased UVs in group " + x.label )
           x.vertices_nouv = True
    return mesh


def group_compare( grp1, grp2 ):
    """compares mesh groups in regards to texture id, material id (and label)"""
    if grp1.texture < grp2.texture:
        if grp1.texture != 0:
            return -1
        else:
            return 1# send groups without texture to end of list
    elif grp1.texture > grp2.texture:
        if grp2.texture != 0:
            return 1
        else:
            return -1# send groups without texture to end of list
    elif grp1.material < grp2.material:
        return -1
    elif grp1.material > grp2.material:
        return 1
    else:
        return 0
#    elif grp1.label > grp2.label:
#        return 1
#    else:
#        return -1


def show_mesh_info( mesh ):
    v = 0
    t = 0
    for x in mesh.grp:
        v = v + x.geom_v
        t = t + x.geom_t
    print( "Group count:", mesh.grpcount )
    print( "Vertex count:", v )
    print( "Triangle count:", t )
    print( "Material count:", mesh.matcount )
    print( "Texture count:", mesh.texcount )
    
    print( "" )
    show_texmat_swap_stats( mesh )
    print( "" )
    show_group_info( mesh )


def show_texmat_swap_stats( mesh ):
    """calc and show texture and material swap count"""
    tex = -1
    mat = -1
    swap_t = 0
    swap_m = 0
    for x in mesh.grp:
        if x.texture != tex:
            tex = x.texture
            swap_t = swap_t + 1
        if x.material != mat:
            mat = x.material
            swap_m = swap_m + 1
            
    print( "Material swaps: " + str( swap_m ) + "\nTexture swaps: " + str( swap_t ) )


def show_group_info( mesh ):
    print( "Mesh Group List:" )
    print( "Tex Mat Label" )
    for x in mesh.grp:
        print( f"{x.texture:3d}", f"{x.material:3d}", x.label )


def load_mesh_from_file( filename, mesh ):
    # mesh data
    mesh.staticmesh = False
    mesh.grpcount = 0
    mesh.grp = []
    mesh.matcount = 0
    mesh.texcount = 0
    mesh.matlist = ""
    mesh.texlist = ""
    
    # temp variables
    lbl = ""
    mat = -1
    tex = -1
    flag = -1
    nonormal = False
    texwrap = ""
    zbias = 0
    static = False
    dynamic = False
    geom_v = 0
    geom_t = 0
    vtx = ""
    tri = ""
    
    dlog = False
    
    grpcounter = 0
    print( "Loading Mesh " + filename + "..." )
    with open( filename, "r" ) as fi:
        # read header
        try:
            line = fi.readline()
            if line.startswith( "MSHX1" ) == False:
                print( "ERROR: No MSHX1 tag" )
                return 1
        
            line = fi.readline()
            if line.startswith( "STATICMESH" ):
                mesh.staticmesh = True
                line = fi.readline()# read next line, which should be GROUPS
            if line.startswith( "GROUPS" ):
                splitstrlist = line.split( " ", 1 )
                mesh.grpcount = int( splitstrlist[1] )
            else:
                print( "ERROR: No GROUPS field" )
                return 2
        except SystemExit:
            return 3# don't display error message below for self-triggered exits
        except:
            print( "ERROR: Header parsing" )
            return 4
        
        # read groups
        try:
            for g in range( mesh.grpcount ):
                lbl = ""
                geom_v = 0
                geom_t = 0
                flag = -1
                nonormal = False
                texwrap = ""
                zbias = 0
                static = False
                dynamic = False
                grpcounter += 1
                while True:
                    line = fi.readline()
                    if line.startswith( "LABEL" ):
                        splitstrlist = cleanline( line ).split( " " )
                        lbl = splitstrlist[1]
                    elif line.startswith( "MATERIAL" ):
                        splitstrlist = cleanline( line ).split( " " )
                        mat = int( splitstrlist[1] )
                    elif line.startswith( "TEXTURE" ):
                        splitstrlist = cleanline( line ).split( " " )
                        tex = int( splitstrlist[1] )
                    elif line.startswith( "FLAG" ):
                        splitstrlist = cleanline( line ).split( " " )
                        flag = int( splitstrlist[1] )
                    elif line.startswith( "NONORMAL" ):
                        nonormal = True
                    elif line.startswith( "TEXWRAP" ):
                        splitstrlist = cleanline( line ).split( " " )
                        texwrap = splitstrlist[1]
                    elif line.startswith( "ZBIAS" ):
                        splitstrlist = cleanline( line ).split( " " )
                        zbias = int( splitstrlist[1] )
                    elif line.startswith( "STATIC" ):
                        static = True
                    elif line.startswith( "DYNAMIC" ):
                        dynamic = True
                    elif line.startswith( "GEOM" ):
                        splitstrlist = cleanline( line ).split( " " )
                        geom_v = int( splitstrlist[1] )
                        geom_t = int( splitstrlist[2] )
                    else:
                        # check for group validity: GEOM must exist, and a texture and material indexes must be defined
                        if geom_v == 0:
                            print( f"ERROR: No vertex count (group {grpcounter})" )
                            return 5
                        elif geom_t == 0:
                            print( f"ERROR: No triangle count (group {grpcounter})" )
                            return 6
                        elif mat == -1:
                            print( f"ERROR: No material index (group {grpcounter})" )
                            return 7
                        elif tex == -1:
                            print( f"ERROR: No texture index (group {grpcounter})" )
                            return 8
                        # read vertices and triangles
                        vtx_nouv = True# true only if all vertices don't have UVs
                        vtx_x = []
                        vtx_y = []
                        vtx_z = []
                        vtx_nx = []
                        vtx_ny = []
                        vtx_nz = []
                        vtx_u = []
                        vtx_v = []
                        
                        for v in range( geom_v ):
                            if dlog == True:
                                print( f"LOG: parsing vtx {v}" )
                            if v == 0:
                                splitstrlist = cleanline( line ).split( " " )
                            else:
                                splitstrlist = cleanline( fi.readline() ).split( " " )
                            vtx_x.append( float( splitstrlist[0] ) )
                            vtx_y.append( float( splitstrlist[1] ) )
                            vtx_z.append( float( splitstrlist[2] ) )
                            
                            _vtx_u = 0.0
                            _vtx_v = 0.0
                            if nonormal:
                                if len( splitstrlist ) == 5:# check if it has UVs
                                    _vtx_u = float( splitstrlist[3] )
                                    _vtx_v = float( splitstrlist[4] )
                                    vtx_nouv = False
                            else:
                                vtx_nx.append( float( splitstrlist[3] ) )
                                vtx_ny.append( float( splitstrlist[4] ) )
                                vtx_nz.append( float( splitstrlist[5] ) )
                                if len( splitstrlist ) == 8:# check if it has UVs
                                    _vtx_u = float( splitstrlist[6] )
                                    _vtx_v = float( splitstrlist[7] )
                                    vtx_nouv = False
                            
                            vtx_u.append( _vtx_u )
                            vtx_v.append( _vtx_v )
                        
                        tri = ""
                        for t in range( geom_t ):
                            if dlog == True:
                                print( f"LOG: parsing tri {t}" )
                            tri = tri + fi.readline()
                        break
                
                # add group to list
                mesh.grp.append( MeshGroup( lbl, mat, tex, flag, nonormal, texwrap, zbias, static, dynamic, geom_v, geom_t, vtx_x, vtx_y, vtx_z, vtx_nx, vtx_ny, vtx_nz, vtx_u, vtx_v, vtx_nouv, tri ) )
        except SystemExit:
            return 9# don't display error message below for self-triggered exits
        except:
            print( f"ERROR: Group parsing (group {grpcounter})" )
            return 10
        
        # read material list
        try:
            line = fi.readline()
            if line.startswith( "MATERIALS" ):
                splitstrlist = line.split( " " )
                mesh.matcount = int( splitstrlist[1] )
                for m in range( mesh.matcount * 6 ):
                    mesh.matlist = mesh.matlist + fi.readline()
            else:
                print( "ERROR: No MATERIALS field" )
                return 11
        except SystemExit:
            return 12# don't display error message below for self-triggered exits
        except:
            print( "ERROR: MATERIALS parsing" )
            return 13
        
        # read texture list
        try:
            line = fi.readline()
            if line.startswith( "TEXTURES" ):
                splitstrlist = line.split( " " )
                mesh.texcount = int( splitstrlist[1] )
                for t in range( mesh.texcount ):
                    mesh.texlist = mesh.texlist + fi.readline()
            else:
                print( "ERROR: No TEXTURES field" )
                return 14
        except SystemExit:
            return 15# don't display error message below for self-triggered exits
        except:
            print( "ERROR: TEXTURES parsing" )
            return 16
    return 0

def dump_mesh_to_file( filename, mesh ):
    print( "Saving Mesh " + filename + "..." )
    with open( filename, "w" ) as fo:
        fo.write( "MSHX1\n" )
        if mesh.staticmesh:
            fo.write( "STATICMESH\n" )
        fo.write( "GROUPS " + str( mesh.grpcount ) + "\n" )
        
        for g in mesh.grp:
            if g.label != "":
                fo.write( "LABEL " + g.label + "\n" )
            fo.write( "MATERIAL " + str( g.material ) + "\n" )
            fo.write( "TEXTURE " + str( g.texture ) + "\n" )
            if g.flag != -1:
                fo.write( "FLAG " + str( g.flag ) + "\n" )
            if g.nonormal:
                fo.write( "NONORMAL\n" )
            if g.texwrap != "":
                fo.write( "TEXWRAP " + g.texwrap + "\n" )
            if g.zbias != 0:
                fo.write( "ZBIAS " + str( g.zbias ) + "\n" )
            if g.static:
                fo.write( "STATIC\n" )
            if g.dynamic:
                fo.write( "DYNAMIC\n" )
            fo.write( "GEOM " + str( g.geom_v ) + " " + str( g.geom_t ) + "\n" )
            if g.nonormal:
                if g.vertices_nouv:
                    # x y z
                    for v in range( g.geom_v ):
                        fo.write( f"{g.vertices_x[v]:g} {g.vertices_y[v]:g} {g.vertices_z[v]:g}\n" )
                else:
                    # x y z u v
                    for v in range( g.geom_v ):
                        fo.write( f"{g.vertices_x[v]:g} {g.vertices_y[v]:g} {g.vertices_z[v]:g} {g.vertices_u[v]:g} {g.vertices_v[v]:g}\n" )
            else:
                if g.vertices_nouv:
                    # x y z nx ny nz
                    for v in range( g.geom_v ):
                        fo.write( f"{g.vertices_x[v]:g} {g.vertices_y[v]:g} {g.vertices_z[v]:g} {g.vertices_nx[v]:g} {g.vertices_ny[v]:g} {g.vertices_nz[v]:g}\n" )
                else:
                    # x y z nx ny nz u v
                    for v in range( g.geom_v ):
                        fo.write( f"{g.vertices_x[v]:g} {g.vertices_y[v]:g} {g.vertices_z[v]:g} {g.vertices_nx[v]:g} {g.vertices_ny[v]:g} {g.vertices_nz[v]:g} {g.vertices_u[v]:g} {g.vertices_v[v]:g}\n" )
            
            fo.write( g.triangles )
        fo.write( "MATERIALS " + str( mesh.matcount ) + "\n" )
        fo.write( mesh.matlist )
        fo.write( "TEXTURES " + str( mesh.texcount ) + "\n" )
        fo.write( mesh.texlist )


################################################################
################################################################


print( "\n" )
print( "####################################" )
print( "#                                  #" )
print( "#     SSV Mesh Tool Box script     #" )
print( "#                                  #" )
print( "####################################\n\n" )

# meshes
mesh1 = Mesh( False, 0, [], 0, 0, "", "" )
mesh2 = Mesh( False, 0, [], 0, 0, "", "" )

# task variables
task_reorder = False
task_deleteUVs = False
task_fixneg0 = False

# temp variables
inputmeshfile = ""
outputmeshfile = ""

# handle arguments
for sw in sys.argv:
    if "-i" in sw:
        inputmeshfile = sw[2:]
    elif "-o" in sw:
        outputmeshfile = sw[2:]
    elif "-h" in sw:
        printhelp()
        sys.exit()
    elif "-r" in sw:
        task_reorder = True
    elif "-u" in sw:
        task_deleteUVs = True
    elif "-z" in sw:
        task_fixneg0 = True

if inputmeshfile == "":
    print( "No input file specified" )
    sys.exit()

if outputmeshfile == "":
    print( "No output file specified" )
    sys.exit()
    
if (task_reorder == False) & (task_deleteUVs == False) & (task_fixneg0 == False):
    print( "No task specified" )
    sys.exit()


# read original mesh file
load_mesh_from_file( inputmeshfile, mesh1 )

# mesh info
print( "\n**Input Mesh Info**" )
show_mesh_info( mesh1 )


# tasks
# re-order groups
if task_reorder == True:
    print( "\nRe-ordering mesh groups..." )
    mesh1 = reorder_mesh_groups( mesh1 )

# delete UV coordinates on groups that use no texture (TEXTURE 0)
if task_deleteUVs == True:
    print( "\nDeleting UV coordinates..." )
    mesh1 = eraseUV( mesh1 )

# fix negative 0
if task_fixneg0 == True:
    print( "\nFixing negative 0 not implemented yet..." )


# new mesh stats
print( "\n**Output Mesh Stats**" )
show_mesh_info( mesh1 )


# output new mesh file
dump_mesh_to_file( outputmeshfile, mesh1 )

print( "\nSSV Mesh Tool Box script complete!" )
