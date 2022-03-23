#!BPY
# Copyright (c) 2008-2012 AJ
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
Name: 'GUNZ (*.elu, *.ani)...'
Blender: 246
Group: 'Import'
Tooltip: 'Import GUNZ *.elu and/or *.ani game files'
"""

__author__ = 'AJ'
__email__ = ''
__url__ = ('blender', 'elysiun', 'Project homepage, http://www.ragezone.com/')
__version__ = '11.11.05'
__bpydoc__ = """ \
This script imports GUNZ *.elu and/or *.ani game files.
"""


import Blender
import bpy
import math
import struct


ELU_VERSIONS = (0x5004, 0x5005, 0x5006, 0x5007)

ANI_VERSIONS = (0x12, 0x1001, 0x1002, 0x1003)

ANI_FORMAT = 2

DOT_DDS = '.dds'

SOFT_BODY_GROUP = 'SoftBody'

MAX_INFLUENCES = 4

FACE_VERTEX_COUNT = 3


class MagicError(ValueError):
    pass


class VersionError(ValueError):
    pass


class FormatError(ValueError):
    pass


def elu_to_blender_name(name):
    if name.startswith('Bip01 L ') is True:
        return "%s %s.L" % ('Bip01', name[8:])

    if name.startswith('Bip01 R ') is True:
        return "%s %s.R" % ('Bip01', name[8:])

    return name


def elu_read_material(file_object):
    high_index, \
    low_index = struct.unpack('<2I', file_object.read(8))

    print "material %d-%d start 0x%x" % (high_index, low_index, file_object.tell() - 8)

    ambient_color = struct.unpack('<4f', file_object.read(16))
    diffuse_color = struct.unpack('<4f', file_object.read(16))
    specular_color = struct.unpack('<4f', file_object.read(16))
    specular_power = struct.unpack('<f', file_object.read(4))[0]

    unknown_0 = struct.unpack('<I', file_object.read(4))[0]

    material_name = "Mat.%03d" % high_index

    material = None

    try:
        material = Blender.Material.Get(material_name)
    except:
        material = Blender.Material.New(material_name)

        if material is not None:
            material.setRGBCol(diffuse_color[0:3])
            material.setAlpha(diffuse_color[3])
            material.setSpecCol(specular_color[0:3])
            material.setSpec(specular_power)

    print "material %d-%d end 0x%x" % (high_index, low_index, file_object.tell())

    return material


def elu_search_for_path(search_names, search_extensions, search_paths):
    for search_path in search_paths:
        search_path_0 = Blender.sys.cleanpath(search_path)

        if Blender.sys.exists(search_path_0) == 2:
            for search_name in search_names:
                search_path_1 = Blender.sys.join(search_path_0, search_name)

                for search_extension in search_extensions:
                    search_path_2 = Blender.sys.makename(search_path_1, search_extension)

                    if Blender.sys.exists(search_path_2) == 1:
                        return search_path_2

    return None


def elu_load_image(image_path):
    image = None

    image_name = Blender.sys.makename(image_path, strip=1)

    try:
        image = Blender.Image.Get(image_name)
    except:
        try:
            image = Blender.Image.Load(image_path)
        except:
            Blender.Draw.PupMenu("Warning%%t|Could not load %s" % image_path)
        else:
            image.setName(image_name)

    return image


def elu_read_texture(file_object, version):
    texture_name_1 = ''
    texture_name_2 = ''

    if version == 0x5004 or version == 0x5005:
        texture_name_1 = file_object.read(40)
        texture_name_2 = file_object.read(40)
    elif version == 0x5006 or version == 0x5007:
        texture_name_1 = file_object.read(256)
        texture_name_2 = file_object.read(256)

    texture_name_1 = texture_name_1[0:texture_name_1.find('\0')]

    if version == 0x5004 or version == 0x5005:
        print "texture %s start 0x%x" % (texture_name_1, file_object.tell() - 40)
    elif version == 0x5006 or version == 0x5007:
        print "texture %s start 0x%x" % (texture_name_1, file_object.tell() - 256)

    texture_name_1, texture_extension_1 = Blender.sys.splitext(texture_name_1)

    texture = None

    try:
        texture = Blender.Texture.Get(texture_name_1)
    except:
        texture = Blender.Texture.New(texture_name_1)

        if texture is not None:
            search_names = [texture_name_1]

            search_extensions = [texture_extension_1, DOT_DDS, texture_extension_1 + DOT_DDS]

            search_paths = [Blender.sys.dirname(file_object.name), Blender.Get('texturesdir'), '//']

            found_path = elu_search_for_path(search_names, search_extensions, search_paths)

            if found_path is not None:
                image = elu_load_image(found_path)

                if image is not None:
                    texture.setType('Image')
                    texture.setImage(image)
                    texture.setImageFlags('UseAlpha')
                    texture.setExtend('Clip')
            else:
                Blender.Draw.PupMenu("Warning%%t|Could not locate %s" % Blender.sys.makename(texture_name_1, texture_extension_1))

    print "texture %s end 0x%x" % (texture_name_1, file_object.tell())

    return texture


def elu_read_material_texture(file_object, version):
    material = elu_read_material(file_object)

    texture = elu_read_texture(file_object, version)

    two_sided, \
    additive = struct.unpack('<2I', file_object.read(8))

    alpha_percentage = 0

    if version == 0x5007:
        alpha_percentage = struct.unpack('<I', file_object.read(4))[0]

    if material is not None:
        material.properties['isTwoSided'] = two_sided # Applied on faces

        material.setAlpha(1.0 - float(alpha_percentage / 100))

        material_mode = material.getMode()

        if texture is not None:
            material_textures = material.getTextures()

            material_texture_index = -1

            for i, material_texture in enumerate(material_textures):
                if material_texture is None:
                    material_texture_index = i
                    break

            if material_texture_index >= 0:
                material.setTexture(material_texture_index, texture, Blender.Texture.TexCo.UV)

                material_mode |= Blender.Material.Modes.TEXFACE
                material_mode |= Blender.Material.Modes.ZTRANSP

                if alpha_percentage == 0:
                    material_mode |= Blender.Material.Modes.TEXFACE_ALPHA

                if additive > 0:
                    material_textures = material.getTextures()

                    material_texture = material_textures[material_texture_index]

                    if material_texture is not None:
                        material_texture.blendmode |= Blender.Texture.BlendModes.ADD

        material.setMode(material_mode)

    return material


def elu_read_mesh(file_object, version, scene=None):
    if scene is None:
        scene = Blender.Scene.GetCurrent()

    mesh_name = file_object.read(40)
    parent_mesh_name = file_object.read(40)

    mesh_name = mesh_name[0:mesh_name.find('\0')]
    parent_mesh_name = parent_mesh_name[0:parent_mesh_name.find('\0')]

    mesh_name = elu_to_blender_name(mesh_name)
    parent_mesh_name = elu_to_blender_name(parent_mesh_name)

    print "mesh %s-%s start 0x%x" % (mesh_name, parent_mesh_name, file_object.tell() - 80)

    mesh = Blender.Mesh.New(mesh_name)

    mesh_object = scene.objects.new(mesh)

    wm = struct.unpack('<16f', file_object.read(64))

    world_matrix = Blender.Mathutils.Matrix([wm[0], wm[2], wm[1], wm[3]], \
                                            [wm[8], wm[10], wm[9], wm[11]], \
                                            [wm[4], wm[6], wm[5], wm[7]], \
                                            [wm[12], wm[14], wm[13], wm[15]])

    file_object.seek(44, 1) # Eleven single precision floats: scale vector, rotation vector, rotation angle, scale pivot vector, scale pivot angle

    lm = struct.unpack('<16f', file_object.read(64))

    local_matrix = Blender.Mathutils.Matrix([lm[0], lm[2], lm[1], lm[3]], \
                                            [lm[8], lm[10], lm[9], lm[11]], \
                                            [lm[4], lm[6], lm[5], lm[7]], \
                                            [lm[12], lm[14], lm[13], lm[15]])

    vertex_position_count = struct.unpack('<I', file_object.read(4))[0]

#    print "\tvertex position count %d" % vertex_position_count

    for x in xrange(vertex_position_count):
        px, py, pz = struct.unpack('<3f', file_object.read(12))

        position = Blender.Mathutils.Vector(px, pz, py)

        mesh.verts.extend(position)

    face_count = struct.unpack('<I', file_object.read(4))[0]

#    print "\tface count %d" % face_count

    face_diffs = []

    smooth_groups = {}

    for x in xrange(face_count):
        face_indices = [i for i in struct.unpack('<3I', file_object.read(12))] # Tri-face

        face_indices.reverse()

        face_vertices = [mesh.verts[i] for i in face_indices]

        face_index = mesh.faces.extend(*face_vertices, indexList=True)[0]

        # Check if duplicate
        if face_index is not None:
            face = mesh.faces[face_index]

            # This is a hack for when Blender decides to alter the face culling
            face_diff = [face_indices.index(v.index) for v in face.verts]

            face_diff.append(face_index)

            face_diffs.append(face_diff)

            face_uvs = []

            # Allocate because of hack above
            for x in xrange(FACE_VERTEX_COUNT):
                face_uvs.append(Blender.Mathutils.Vector(0.0, 0.0))

            for x in xrange(FACE_VERTEX_COUNT):
                u, v, w = struct.unpack('<3f', file_object.read(12))

                face_uvs[face_diff[x]] = Blender.Mathutils.Vector(u, float(1.0 - v))

            face_uvs.reverse()

            face.uv = tuple(face_uvs)
            face.transp = Blender.Mesh.FaceTranspModes.SOLID

            material_index, \
            smooth_group_index = struct.unpack('<2I', file_object.read(8))

            if smooth_group_index in smooth_groups:
                smooth_groups[smooth_group_index].extend([v.index for v in face.verts])
            else:
                smooth_groups[smooth_group_index] = [v.index for v in face.verts]
        else:
            face_diffs.append(None)

            file_object.seek(44, 1) # Skip duplicate

    for smooth_group_index, smooth_group_vertices in smooth_groups.iteritems():
        smooth_group_name = "Smooth.%03d" % smooth_group_index

        mesh.addVertGroup(smooth_group_name)

        mesh.assignVertsToGroup(smooth_group_name, \
                                smooth_group_vertices, \
                                1.0, \
                                Blender.Mesh.AssignModes.ADD)

        smooth_modifier = mesh_object.modifiers.append(Blender.Modifier.Types.SMOOTH)

        smooth_modifier[Blender.Modifier.Settings.FACTOR] = 0.0 # let the user modify
        smooth_modifier[Blender.Modifier.Settings.VERTGROUP] = smooth_group_name

    material_index = 0

    if version >= 0x5005 and version <= 0x5007:
        for face_diff in face_diffs:
            if face_diff is not None:
                face_index = face_diff.pop()

                face = mesh.faces[face_index]

                face_normal = Blender.Mathutils.Vector(struct.unpack('<3f', file_object.read(12))) # can't be assigned in blender, face.no read-only

                vertex_normals = []

                # Allocate because of hack above
                for x in xrange(FACE_VERTEX_COUNT):
                    vertex_normals.append(Blender.Mathutils.Vector(0.0, 0.0, 0.0))

                for x in xrange(FACE_VERTEX_COUNT):
                    nx, ny, nz = struct.unpack('<3f', file_object.read(12))

                    vertex_normals[face_diff[x]] = Blender.Mathutils.Vector(nx, nz, ny)

                vertex_normals.reverse()

                for j, vertex in enumerate(face):
                    vertex.no = vertex_normals[j]
            else:
                file_object.seek(48, 1) # Skip duplicate

        vertex_color_count = struct.unpack('<I', file_object.read(4))[0]

#        print "\tvertex color count %d" % vertex_color_count

        goal_weights = []

        vertex_colors = []

        if vertex_color_count > 0:
            mesh.addVertGroup(SOFT_BODY_GROUP) # blender soft-body vertex group, you'll need to apply as goal manualy

        for x in xrange(vertex_color_count):
            vertex_color = struct.unpack('<3f', file_object.read(12))

            goal_weights.append(math.fsum(vertex_color) / 3.0)

            mesh.assignVertsToGroup(SOFT_BODY_GROUP, \
                                    [x], \
                                    goal_weights[x], \
                                    Blender.Mesh.AssignModes.ADD)

            vertex_colors.append([int(y * 255.0) for y in vertex_color])

        if vertex_color_count > 0:
            mesh.vertexColors = True

            for face in mesh.faces:
                for i, vertex in enumerate(face):
                    vertex_color = vertex_colors[vertex.index]

                    face_color = face.col[i]
                    face_color.r = vertex_color[0]
                    face_color.g = vertex_color[1]
                    face_color.b = vertex_color[2]

        material_index = struct.unpack('<I', file_object.read(4))[0]

        bone_influence_count = struct.unpack('<I', file_object.read(4))[0]

#        print "\tbone influence count %d" % bone_influence_count

        for x in xrange(bone_influence_count):
            bone_influence_names = []

            for y in xrange(MAX_INFLUENCES):
                bone_influence_name = file_object.read(40)
                bone_influence_name = bone_influence_name[0:bone_influence_name.find('\0')]

                if len(bone_influence_name) > 0:
                    bone_influence_name = elu_to_blender_name(bone_influence_name)

                    bone_influence_names.append(bone_influence_name)

            bone_influence_weights = [y for y in struct.unpack('<4f', file_object.read(16)) if y > 0.0]

            file_object.seek(16, 1) # Three 32-bit unsigned integers: parent ids, always 0

            # doesn't seem to be reliable... what might be needed is verifying if
            # the sum of the weights is 1.0 just to be safe
            count = struct.unpack('<I', file_object.read(4))[0]

            for y in xrange(len(bone_influence_weights)):
                mesh.addVertGroup(bone_influence_names[y])

                mesh.assignVertsToGroup(bone_influence_names[y], \
                                        [x],
                                        bone_influence_weights[y],
                                        Blender.Mesh.AssignModes.ADD)

            for y in xrange(MAX_INFLUENCES):
                ox, oy, oz = struct.unpack('<3f', file_object.read(12))

                offset = Blender.Mathutils.Vector(ox, oz, oy)
    else:
        file_object.seek(4, 1) # Padding

        material_index = struct.unpack('<I', file_object.read(4))[0]

    try:
        material_name = "Mat.%03d" % material_index

        material = Blender.Material.Get(material_name)
    except:
        pass
    else:
        if material is not None:
            mesh.materials += [material]

            material_textures = material.getTextures()

            for i, material_texture in enumerate(material_textures):
                if material_texture is not None:
                    texture = material_texture.tex

                    if texture is not None:
                        image = texture.getImage()

                        if image is not None:
                            for face in mesh.faces:
                                face_mode = face.mode | Blender.Mesh.FaceModes.TEX

                                if material.properties['isTwoSided'] == 1:
                                    face_mode |= Blender.Mesh.FaceModes.TWOSIDE

                                face.mode = face_mode
                                face.image = image

                    break

    is_joint = int(mesh_name.startswith('Bip'))

    mesh.properties['isJoint'] = is_joint

    if is_joint == 1:
        mesh.hide = True

        mesh_object.setDrawMode(Blender.Object.DrawModes['TRANSP'])

    mesh.update()

    mesh_object.setMatrix(world_matrix)

    mesh_object.addProperty('isJoint', is_joint, 'INT')

    try:
        parent_mesh_object = Blender.Object.Get(parent_mesh_name)
    except:
        pass
    else:
        is_parent_joint = parent_mesh_object.getProperty('isJoint')

        if (is_parent_joint is not None and is_parent_joint.getData() == 1) and is_joint == 1:
            parent_mesh_object.makeParent([mesh_object])

    print "mesh %s-%s end 0x%x" % (mesh_name, parent_mesh_name, file_object.tell())

    return mesh_object


def ani_read_mesh_transformations(file_object, version, armature_object):
    key_frames = {}

    armature_pose = armature_object.getPose()

    armature_pose_bones = armature_pose.bones

    mesh_name = file_object.read(40)

    mesh_name = mesh_name[0:mesh_name.find('\0')]

    mesh_name = elu_to_blender_name(mesh_name)

    print "transform %s start 0x%x" % (mesh_name, file_object.tell() - 44)

    pm = struct.unpack('<16f', file_object.read(64))

    pose_matrix = Blender.Mathutils.Matrix([pm[0], pm[2], pm[1], pm[3]], \
                                           [pm[8], pm[10], pm[9], pm[11]], \
                                           [pm[4], pm[6], pm[5], pm[7]], \
                                           [pm[12], pm[14], pm[13], pm[15]])

    translation_count = struct.unpack('<I', file_object.read(4))[0]

#    print "translation count %d" % translation_count

    for x in xrange(translation_count):
        tx, ty, tz = struct.unpack('<3f', file_object.read(12))

        translation = Blender.Mathutils.Vector(tx, tz, ty)

        key_frame_second = int(struct.unpack('<I', file_object.read(4))[0] / 60)

        translation_matrix = Blender.Mathutils.TranslationMatrix(translation)

        key_frames[key_frame_second] = translation_matrix

    rotation_count = struct.unpack('<I', file_object.read(4))[0]

#    print "rotation count %d" % rotation_count

    for x in xrange(rotation_count):
        rotation_matrix = Blender.Mathutils.Matrix()

        rotation_matrix.identity()

        rx, ry, rz, rw = struct.unpack('<4f', file_object.read(16))

        if version >= 0x1003:
            rotation = Blender.Mathutils.Quaternion(-rw, rx, rz, ry)

            rotation_matrix *= rotation.toMatrix().resize4x4()
        else:
            rotation = Blender.Mathutils.Quaternion([rx, rz, ry], math.degrees(-rw))

            rotation_matrix *= rotation.toMatrix().resize4x4()

        key_frame_second = int(struct.unpack('<I', file_object.read(4))[0] / 60)

        if key_frame_second in key_frames:
            key_frames[key_frame_second] = rotation_matrix * key_frames[key_frame_second]
        else:
            parent_inverse_pose_matrix = Blender.Mathutils.Matrix()

            parent_inverse_pose_matrix.identity()

            if mesh_name in armature_pose_bones.keys():
                if armature_pose_bones[mesh_name].parent is not None:
                    parent_inverse_pose_matrix *= armature_pose_bones[mesh_name].parent.poseMatrix.copy()

            parent_inverse_pose_matrix.invert()

            key_frames[key_frame_second] = rotation_matrix * Blender.Mathutils.TranslationMatrix((pose_matrix * parent_inverse_pose_matrix).translationPart())

    if mesh_name in armature_pose_bones.keys():
        if len(key_frames) > 0:
            for key_frame_second, key_frame_transformation in key_frames.iteritems():
                if armature_pose_bones[mesh_name].parent is not None:
                    key_frame_transformation *= armature_pose_bones[mesh_name].parent.poseMatrix.copy()

                armature_pose_bones[mesh_name].poseMatrix = key_frame_transformation

                armature_pose.update()

                armature_pose_bones[mesh_name].insertKey(armature_object, key_frame_second + 1)

            armature_pose_bones[mesh_name].poseMatrix = pose_matrix

            armature_pose.update()
        else:
            armature_pose_bones[mesh_name].poseMatrix = pose_matrix

            armature_pose.update()

            armature_pose_bones[mesh_name].insertKey(armature_object, 1)

    if version >= 0x1001:
        unknown_0 = struct.unpack('<I', file_object.read(4))[0]

        for x in xrange(unknown_0):
            file_object.seek(8, 1) # 1 single precision float, 1 32-bit unsigned integer

    print "transform %s end 0x%x" % (mesh_name, file_object.tell())


def elu_import(file_path):
    file_object = None

    try:
        scene = Blender.Scene.GetCurrent()

        file_object = open(file_path, 'rb')

        magic, \
        version = struct.unpack('<2I', file_object.read(8))

        if magic != 0x0107F060:
            raise MagicError, "Bad magic number, %x" % magic

#        print "version %d" % version

        if version not in ELU_VERSIONS and version not in ANI_VERSIONS:
            raise VersionError, "Bad version number %d" % version

        if version in ELU_VERSIONS:
            material_count, \
            mesh_count = struct.unpack('<2I', file_object.read(8))

            for x in xrange(material_count):
                elu_read_material_texture(file_object, version)

            joint_mesh_objects = []

            skin_mesh_objects = []

            for x in xrange(mesh_count):
                mesh_object = elu_read_mesh(file_object, version, scene)

                is_joint = mesh_object.getProperty('isJoint')

                if (is_joint is not None and is_joint.getData() == 1) or mesh_object.name.startswith('Bip') is True:
                    joint_mesh_objects.append(mesh_object)
                else:
                    skin_mesh_objects.append(mesh_object)
        elif version in ANI_VERSIONS:
            maximum_frame, \
            mesh_count, \
            animation_format = struct.unpack('<3I', file_object.read(12))

            if animation_format != ANI_FORMAT:
                raise FormatError, "Unsupported animation format %d" % animation_format

            try:
                armature_object = Blender.Object.Get('Armature')
            except ValueError:
                Blender.Draw.PupMenu("Error%%t|The scene does not contain an armature")
            else:
                action_name = Blender.sys.basename(file_object.name)
                action_name = action_name[0:action_name.find('.')]

                action = Blender.Armature.NLA.NewAction(action_name)
                action.setActive(armature_object)

                for x in xrange(mesh_count):
                    ani_read_mesh_transformations(file_object, version, armature_object)
    except IOError, (errno, strerror):
        Blender.Draw.PupMenu("Error%%t|I/O error(%d): %s." % (errno, strerror))
#    except Exception, err:
#        Blender.Draw.PupMenu("Error%%t|.%s" % err)
    else:
        if version in ELU_VERSIONS:
            if len(joint_mesh_objects) > 0:
                armature = Blender.Armature.New('Armature')

                armature.drawType = Blender.Armature.STICK
                armature.envelopes = False
                armature.vertexGroups = True

                armature_object = scene.objects.new(armature)

                armature_object.drawMode = Blender.Object.DrawModes.XRAY

                armature.makeEditable()

                for joint_mesh_object in joint_mesh_objects:
                    edit_bone = Blender.Armature.Editbone()

                    edit_bone.name = joint_mesh_object.name

                    parent_joint_mesh_object = joint_mesh_object.getParent()

                    if parent_joint_mesh_object is not None:
                        edit_bone.parent = armature.bones[parent_joint_mesh_object.name]

                    edit_bone.matrix = joint_mesh_object.getMatrix()

                    armature.bones[edit_bone.name] = edit_bone

                armature.update()

                armature_pose = armature_object.getPose()

                armature_pose_bones = armature_pose.bones

                for armature_pose_bone in armature_pose_bones.values():
                    try:
                        joint_mesh_object = Blender.Object.Get(armature_pose_bone.name)
                    except:
                        pass
                    else:
                        armature_pose_bone.displayObject = joint_mesh_object

                        scene.objects.unlink(joint_mesh_object)

                armature_object.makeParent(skin_mesh_objects)

                armature_object.layers = [2]

                for skin_mesh_object in skin_mesh_objects:
                    skin_mesh_object.layers = [1, 2]

                    armature_modifier = skin_mesh_object.modifiers.append(Blender.Modifier.Types.ARMATURE)

                    armature_modifier[Blender.Modifier.Settings.OBJECT] = armature_object
    finally:
        scene.objects.selected = []

        scene.update(0)

        if file_object is not None:
            file_object.close()


def main():
    def elu_file_selector(file_path):
        if file_path and not Blender.sys.exists(file_path):
            Blender.Draw.PupMenu("Error%%t|The file %s does not exist." % file_path)
        else:
            elu_import(file_path)

    Blender.Window.FileSelector(elu_file_selector, 'Ok', Blender.sys.makename(ext='.elu'))


if __name__ == "__main__":
    main()