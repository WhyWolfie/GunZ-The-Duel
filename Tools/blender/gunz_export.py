#!BPY

# Copyright (c) 2008-2009 Peter S. Stevens
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.


"""
Name: 'GUNZ (*.elu)...'
Blender: 246
Group: 'Export'
Tooltip: 'Export GUNZ *.elu game files'
"""

__author__ = 'Peter S. Stevens'
__email__ = 'pstevens:cryptomail*org'
__url__ = ('blender', 'elysiun', 'Project homepage, http://www.ragezone.com/')
__version__ = '09.12.00'
__bpydoc__ = """ \
This script exports GUNZ *.elu game files.
"""

import Blender
import BPyMesh
import BPyObject
import struct


LEFT_TO_RIGHT = Blender.Mathutils.Matrix([-1.0, 0.0, 0.0, 0.0],
                                         [0.0, 0.0, 1.0, 0.0],
                                         [0.0, 1.0, 0.0, 0.0],
                                         [0.0, 0.0, 0.0, 1.0])


def blender_to_elu_name(name):
    if name.startswith('Bip01 ') == True:
        if name.endswith('.L'):
            return "%s %s" % ('Bip01 L', name[6:-2])
        
        if name.endswith('.R'):
            return "%s %s" % ('Bip01 R', name[6:-2])
    
    return name


def elu_sort_by_parent(a, b):
    if a.getParent() == b:
        return 1
    elif a == b.getParent():
        return -1
    
    return 0


def elu_recursive_bone_insert(bones, bone):
    index = len(bones)
    
    if bone not in bones:
        if bone.hasParent() == True:
            if bone.parent in bones:
                index = bones.index(bone.parent) + 1
            else:
                index = elu_recursive_bone_insert(bones, bone.parent)
        
        bones.insert(index, bone)
        
        index = index + 1
    
    return index


def elu_triangulate_mesh(mesh):
    if any(len(face.verts) == 4 for face in mesh.faces): 
        scene = Blender.Scene.GetCurrent()
        
        old_mesh_mode = Blender.Mesh.Mode()
        
        Blender.Mesh.Mode(Blender.Mesh.SelectModes['FACE'])
        
        mesh.sel = True
        
        temporary_mesh_object = scene.objects.new(mesh)
        
        mesh.quadToTriangle(0)
        
        old_mesh_mode = Blender.Mesh.Mode(old_mesh_mode)
        
        scene.objects.unlink(temporary_mesh_object)
        
        Blender.Mesh.Mode(old_mesh_mode)


def elu_write_material(file_object, material, index):
    file_object.write(struct.pack('<2I', index, 0xFFFFFFFF))
    
    file_object.write(struct.pack('<3f', *material.getRGBCol()))
    file_object.write(struct.pack('<f', material.getAlpha()))
    file_object.write(struct.pack('<3f', *material.getMirCol()))
    file_object.write(struct.pack('<f', material.getAlpha()))
    file_object.write(struct.pack('<3f', *material.getSpecCol()))
    file_object.write(struct.pack('<f', material.getAlpha()))
    file_object.write(struct.pack('<f', material.getSpec()))
    file_object.write(struct.pack('<f', material.getEmit()))


def elu_write_texture(file_object, texture, version):
    image = texture.getImage()
    
    if image is None:
        raise AttributeError, "Texture (%s) has no image." % texture.getName()
    
    image_file_name =  Blender.sys.basename(image.getFilename())
    
    image_file_name = image_file_name.replace('.dds', '')
    
    image_name = ''
    
    if version == 0x5004 or version == 0x5005:
        image_name = struct.pack('<40s', image_file_name)
    elif version == 0x5006 or version == 0x5007:
        image_name = struct.pack('<256s', image_file_name)
    
    file_object.write(image_name)
    
    file_object.write(image_name)
    
    file_object.write(struct.pack('<2I', 1, 0)) # double sided: should check face mode for Blender.Mesh.FaceModes.TWOSIDE
    
    if version == 0x5007:
        if texture.useAlpha != 0: #(texture.fields & Blender.Texture.USEALPHA) == Blender.Texture.USEALPHA:
            file_object.write(struct.pack('<I', 100))
        else:
            file_object.write(struct.pack('<I', 0))


def elu_write_mesh(file_object, mesh, parent_mesh, world_matrix, local_matrix, material_index, version):
    file_object.write(struct.pack('<40s', blender_to_elu_name(mesh.name)))
    
    if parent_mesh is not None:
        file_object.write(struct.pack('<40s', blender_to_elu_name(parent_mesh.name)))
    else:
        file_object.write(struct.pack('<40x'))
    
    file_object.write(struct.pack('<4f', *world_matrix[0]))
    file_object.write(struct.pack('<4f', *world_matrix[1]))
    file_object.write(struct.pack('<4f', *world_matrix[2]))
    file_object.write(struct.pack('<4f', *world_matrix[3]))
    
    file_object.write(struct.pack('<44x'))
    
    file_object.write(struct.pack('<4f', *local_matrix[0]))
    file_object.write(struct.pack('<4f', *local_matrix[1]))
    file_object.write(struct.pack('<4f', *local_matrix[2]))
    file_object.write(struct.pack('<4f', *local_matrix[3]))
    
    file_object.write(struct.pack('<I', len(mesh.verts)))
    
    for vertex in mesh.verts:
        file_object.write(struct.pack('<3f', *vertex.co))
    
    file_object.write(struct.pack('<I', len(mesh.faces)))
    
    for face in mesh.faces:
        file_object.write(struct.pack('<3I', *[vertex.index for vertex in face.verts]))
        
        if mesh.faceUV == 1:
            for uv in face.uv:
                file_object.write(struct.pack('<2f', uv.x, float(1 - uv.y)))
                
                file_object.write(struct.pack('<4x'))
        else:
            for x in xrange(3):
                file_object.write(struct.pack('<12x'))
        
        file_object.write(struct.pack('<2I', 1, 1))
#        file_object.write(struct.pack('<8x'))
    
    if version >= 0x5005 and version <= 0x5007:
        for face in mesh.faces:
            file_object.write(struct.pack('<3f', *face.no))
            
            for vertex in face.verts:
                file_object.write(struct.pack('<3f', *vertex.no))
        
        if mesh.vertexColors == 0:
            file_object.write(struct.pack('<I', 0))
        else:
            vertex_colors = []
            
            for vertex in mesh.verts:
                vertex_colors.append((1.0, 1.0, 1.0))
            
            for face in mesh.faces:
                for i, vertex in enumerate(face):
                    face_color = face.col[i]
                    
                    red = float(face_color.r) / 255.0
                    green = float(face_color.g) / 255.0
                    blue = float(face_color.b) / 255.0
                    
                    vertex_colors[vertex.index] = (red, green, blue)
            
            file_object.write(struct.pack('<I', len(vertex_colors)))
            
            for vertex_color in vertex_colors:
                file_object.write(struct.pack('<3f', *vertex_color))
        
        file_object.write(struct.pack('<I', material_index))
        
        if len(mesh.getVertGroupNames()) == 0:
            file_object.write(struct.pack('<I', 0))
        else:
            file_object.write(struct.pack('<I', len(mesh.verts)))
            
            for vertex in mesh.verts:
                vertex_influences = mesh.getVertexInfluences(vertex.index)
                
                vertex_weights = []
                
                for vertex_group, vertex_weight in vertex_influences:
                    file_object.write(struct.pack('<40s', blender_to_elu_name(vertex_group)))
                    
                    vertex_weights.append(vertex_weight)
                
                if len(vertex_weights) < 4:
                    file_object.write(struct.pack("<%dx" % ((4 - len(vertex_weights)) * 40)))
                
                file_object.write(struct.pack("<%df" % len(vertex_weights), *vertex_weights))
                
                if len(vertex_weights) < 8:
                    file_object.write(struct.pack("<%dx" % ((8 - len(vertex_weights)) * 4)))
                
                file_object.write(struct.pack('<I', len(vertex_weights)))
                
                file_object.write(struct.pack('<48x'))
    else:
        file_object.write(struct.pack('<4x'))
        file_object.write(struct.pack('<I', material_index))


def elu_bone_to_mesh(bone):
    mesh = Blender.Mesh.Primitives.UVsphere(8, 8, 2.0)
    
    mesh_object = Blender.Object.Get(bone.name)
    
    if mesh_object is None:
        mesh_object = Blender.Object.New('Mesh', bone.name)
    else:
        mesh_object.clrParent()
    
    mesh_object.link(mesh)
    
    mesh.name = bone.name
    
    mesh.update()
    
    world_matrix = bone.matrix['ARMATURESPACE'].copy()
    
    mesh_object.setMatrix(world_matrix)
    
    if bone.hasParent() == True:
        mesh_object_parent = Blender.Object.Get(bone.parent.name)
        
        if mesh_object_parent is not None:
            mesh_object_parent.makeParent([mesh_object])
    
    return mesh_object


def elu_export(file_path):
    mesh_objects = []
    armature_objects = []
    meshes = []
    materials = []
    material_textures = []
    mesh_parents = []
    mesh_world_matrices = []
    mesh_local_matrices = []
    mesh_material_indices = []
    temporary_mesh_objects = []
    
    version = Blender.Draw.Create(4)
    
    block = [('Version: ', version, 4, 7)]
    
    option = Blender.Draw.PupBlock('Export Options', block)
    
    version.val += 0x5000
    
    scene = Blender.Scene.GetCurrent()
    
    scene.update(0)
    
    selected_objects = Blender.Object.GetSelected()
    
    if len(selected_objects) == 0:
        raise IndexError, 'No objects selected.'
    
    for selected_object in selected_objects:
        if selected_object.getType() == 'Mesh':
            for derived_object, derived_object_world_matrix in BPyObject.getDerivedObjects(selected_object, False):
                if derived_object not in mesh_objects:
                    mesh_objects.append(derived_object)
        elif selected_object.getType() == 'Armature':
            armature_objects.append(selected_object)
    
    if len(mesh_objects) == 0:
        raise IndexError, 'No mesh objects selected.'
    else:
        mesh_objects.sort(elu_sort_by_parent)
    
    if len(armature_objects) == 1:
        armature = armature_objects[0].getData()
        
        bones = []
        
        for bone in armature.bones.values():
            elu_recursive_bone_insert(bones, bone)
        
        for bone in bones:
            mesh_object = elu_bone_to_mesh(bone)
            
            scene.objects.link(mesh_object)
            
            temporary_mesh_objects.append(mesh_object)
        
        if len(temporary_mesh_objects) > 0:
            mesh_objects.extend(temporary_mesh_objects)
    
    for mesh_object in mesh_objects:
        mesh = mesh_object.getData(mesh = True)
        
        elu_triangulate_mesh(mesh)
        
        world_matrix = mesh_object.getMatrix('worldspace').copy()
        world_matrix *= LEFT_TO_RIGHT
        
        local_matrix = mesh_object.getMatrix('localspace').copy()
        local_matrix *= LEFT_TO_RIGHT
        
#        BPyMesh.meshCalcNormals(mesh)
        mesh.calcNormals()
        
        meshes.append(mesh)
        
        mesh_world_matrices.append(world_matrix)
        
        mesh_local_matrices.append(local_matrix)
        
        mesh_object_parent = mesh_object.getParent()
        
        if mesh_object_parent is not None and mesh_object_parent in mesh_objects:
            mesh_object_index = mesh_objects.index(mesh_object_parent)
            
            mesh_parents.append(meshes[mesh_object_index])
            
            if mesh_object.name.startswith('Bip') == False:
                mesh_world_matrices[-1] = mesh_world_matrices[mesh_object_index] * mesh_world_matrices[-1]
        else:
            mesh_parents.append(None)
    
    for mesh in meshes:
        mesh_materials = mesh.materials
        
        if len(mesh_materials) > 0:
            material = None
            
            try:
                material = (mm for mm in mesh_materials if mm is not None).next()
            except StopIteration:
                pass
            else:
                material_index = 0
                
                if material not in materials:
                    textures = material.getTextures()
                    
                    if len(textures) == 0:
                        raise AttributeError, "Material (%s) does not contain any textures." % material.getName()
                    else:
                        texture = textures[0].tex
                        
                        material_textures.append(texture)
                    
                    materials.append(material)
                    
                    material_index = len(materials) - 1
                else:
                    material_index = materials.index(material)
                
                mesh_material_indices.append(material_index)
        else:
            if mesh_object.name.startswith('Bip') == True:
                mesh_material_indices.append(0)
            else:
                raise AttributeError, "Mesh (%s) has no assigned materials." % mesh.name
    
    file_object = None
    
    try:
        file_object = open(file_path, 'wb')
        
        file_object.write(struct.pack('<I', 0x0107F060))
        
        file_object.write(struct.pack('<I', version.val))
        
        file_object.write(struct.pack('<I', len(materials)))
        
        file_object.write(struct.pack('<I', len(mesh_objects)))
        
        for x, material in enumerate(materials):
            elu_write_material(file_object, material, x)
            elu_write_texture(file_object, material_textures[x], version.val)
        
        for x, mesh in enumerate(meshes):
            elu_write_mesh(file_object, mesh, mesh_parents[x], mesh_world_matrices[x], mesh_local_matrices[x], mesh_material_indices[x], version.val)
        
        for temporary_mesh_object in temporary_mesh_objects:
            temporary_mesh = temporary_mesh_object.getData(mesh = True)
#            temporary_mesh = BPyMesh.getMeshFromObject(temporary_mesh_object)
            
            scene.objects.unlink(temporary_mesh_object)
            
            if temporary_mesh.users == 0:
                temporary_mesh.faces = None
                temporary_mesh.verts = None
        
        scene.update(0)
    except IOError, (error_number, error_message):
        Blender.Draw.PupMenu("Error%%t|I/O error(%d): %s." % (error_number, error_message))
#    except Exception, error:
#        Blender.Draw.PupMenu("Error%%t|%s." % error)
    finally:
        if file_object is not None:
            file_object.close()


def main():
    def elu_file_selector(file_path):
        if file_path and Blender.sys.exists(file_path):
            option = Blender.Draw.PupMenu("Warning: The file %s exist. Replace it?%%t|Yes|No" % file_path)
            
            if option != 1:
                return
#        try:
        elu_export(file_path)
#        except Exception, error:
#            Blender.Draw.PupMenu("Error%%t|%s." % error)
    
    Blender.Window.FileSelector(elu_file_selector, 'Ok', Blender.sys.makename(ext='.elu'))


if __name__ == "__main__":
    main()