#-------------------------------------------------
#
# Project created by QtCreator 2010-12-08T10:07:50
#
#-------------------------------------------------

cuda.output = "${QMAKE_FILE_NAME}.obj"
cuda.commands = set OLDINCLUDE=%INCLUDE% && set INCLUDE=C:/Program Files/Microsoft Visual Studio 9.0/VC/ATLMFC/INCLUDE";C:/Program Files/Microsoft Visual Studio 9.0/VC/INCLUDE;C:/Program Files//Microsoft SDKs/Windows/v6.0A/include; && \"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v4.0\bin\nvcc.exe\" -gencode=arch=compute_10,code=\\\"sm_20,compute_10\\\"  --machine 32 -ccbin \"C:/Program Files/Microsoft Visual Studio 9.0/VC/bin\"    -Xcompiler \"/EHsc /W3 /nologo /Od /Zi   /MDd  \"  -I\"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v4.0/include\" -I\"C:\Documents and Settings\All Users\Application Data\NVIDIA Corporation\NVIDIA GPU Computing SDK 4.0\C\common\inc\" -I\"C:/ProgramData/NVIDIA Corporation/NVIDIA GPU Computing SDK 4.0/shared/inc\" -maxrregcount=0  --compile -o \"${QMAKE_FILE_OUT}\" \"${QMAKE_FILE_NAME}\" && set INCLUDE=%OLDINCLUDE%
##cuda.commands = set oldinclude=%INCLUDE% && set INCLUDE="C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/ATLMFC/INCLUDE;C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/INCLUDE;C:/Program Files//Microsoft SDKs/Windows/v6.0A/include;" && C:/Progra~1/NVIDIA~2/CUDA/v4.0/bin/nvcc.exe -m64 -ccbin \"C:/Program Files (x86)/Microsoft Visual Studio 9.0/VC/bin\"  -D_DEBUG -D_WIN32   -I\"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v4.0/include\"  -I\"C:/ProgramData/NVIDIA Corporation/NVIDIA GPU Computing SDK 4.0/C/common/inc\" -I\"C:/ProgramData/NVIDIA Corporation/NVIDIA GPU Computing SDK 4.0/shared/inc\" -I\"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v4.0/include\" -I\"C:/ProgramData/NVIDIA Corporation/NVIDIA GPU Computing SDK 4.0/C/common/inc\" -I\"C:/ProgramData/NVIDIA Corporation/NVIDIA GPU Computing SDK 4.0/shared/inc\" -Xcompiler \"/EHsc /W3 /nologo /Od /Zi   /MT  \" -maxrregcount=48 --ptxas-options=-v -keep -gencode=arch=compute_20,code=\\\"sm_20,compute_20\\\"  -c -o \"${QMAKE_FILE_OUT}\" \"${QMAKE_FILE_NAME}\" && set INCLUDE=%oldinclude%
#cuda.commands = set CUDAFE_FLAGS=--sdk_dir \"C:/Program Files (x86)/Microsoft SDKs/Windows/v7.0A/\" && \"C:/Progra~1/NVIDIA~2/CUDA/v4.0/bin/nvcc.exe\" --use-local-env --cl-version 2010 -gencode=arch=compute_20,code=\\\"sm_20,compute_20\\\" -ccbin \"C:/Program Files (x86)/Microsoft Visual Studio 10.0/VC/bin/x86_amd64\" -I\"./\" $(INCPATH) -Xcompiler \"$${QMAKE_CXXFLAGS}\" -maxrregcount=0  --machine 64 --compile  -o \"${QMAKE_FILE_OUT}\" \"${QMAKE_FILE_NAME}\"
#cuda.commands = set CUDAFE_FLAGS=--sdk_dir \"C:\Program Files\Microsoft SDKs\Windows\v6.0A\" && \"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v4.0\bin\nvcc.exe\" --cl-version 2008 -gencode=arch=compute_20,code=\\\"sm_20,compute_20\\\" -ccbin \"C:\Program Files\Microsoft Visual Studio 9.0\VC\bin\" -I\"./\"   -G0  -Xcompiler \"/EHsc /W3 /nologo /Od /Zi   /MDd  \"  -I\"C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v4.0/include\" -I\"C:\Documents and Settings\All Users\Application Data\NVIDIA Corporation\NVIDIA GPU Computing SDK 4.0\C\common\inc\" -I\"C:\Documents and Settings\All Users\Application Data\NVIDIA Corporation\NVIDIA GPU Computing SDK 4.0\shared\inc\"  -maxrregcount=0  --machine 64 --compile  -o \"${QMAKE_FILE_OUT}\" \"${QMAKE_FILE_NAME}\"
cuda.input = CUDA_SOURCES
INCLUDEPATH += "C:/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v4.0/include" "C:\Documents and Settings\All Users\Application Data\NVIDIA Corporation\NVIDIA GPU Computing SDK 4.0\C\common\inc" "C:\Documents and Settings\All Users\Application Data\NVIDIA Corporation\NVIDIA GPU Computing SDK 4.0\shared\inc"
LIBS += -L"C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v4.0\lib\Win32" -L"C:\Documents and Settings\All Users\Application Data\NVIDIA Corporation\NVIDIA GPU Computing SDK 4.0\shared\lib\Win32" -L"C:\Documents and Settings\All Users\Application Data\NVIDIA Corporation\NVIDIA GPU Computing SDK 4.0\C\common\lib\Win32/" -lcudart
DEFINES += _CUDA
QMAKE_EXTRA_COMPILERS += cuda




QT       += opengl

TARGET = VectorFieldProject
TEMPLATE = app
#INCLUDEPATH += /Users/billconan/Downloads/glew-1.5.7/include/
LIBS+= -lglew32

SOURCES +=AxisGlyph.cpp\
Camera.cpp\
CameraPropertyDialog.cpp\
CameraPropertyModel.cpp\
CameraPropertyModelDelegate.cpp\
ColorPickerDialog.cpp\
CoordinateGrid.cpp\
CreateBallDialog.cpp\
CreateBoxDialog.cpp\
CreateCameraDialog.cpp\
CreateCylinderDialog.cpp\
CreateDialog.cpp\
CustomCursorManager.cpp\
DirectionalLight.cpp\
DockWidget.cpp\
DynamicAction.cpp\
FixedOrthogonalCamera.cpp\
GLCanvas.cpp\
GLSLShader.cpp\
GLViewport.cpp\
GraphicsViewBackground.cpp\
Light.cpp\
LightManager.cpp\
MTRand.cpp\
Main.cpp\
MainWindow.cpp\
Material.cpp\
MenuItemWithOptionButton.cpp\
MultipleView.cpp\
MultipleViewToolButton.cpp\
MultiviewBar.cpp\
MultiviewJoint.cpp\
OrthogonalCamera.cpp\
PerspectiveCamera.cpp\
PointLight.cpp\
PropertyDialog.cpp\
Scene.cpp\
SceneDialog.cpp\
SceneItem.cpp\
SceneManagerDialog.cpp\
SceneManagerModel.cpp\
SpotLight.cpp\
StatusbarButton.cpp\
UserCameraManager.cpp\
VectorField.cpp\
Vertex.cpp\
colorpickerwidget.cpp\
colorviewer.cpp\
eig3.cpp\
histogram.cpp\
model.cpp\
qtcolortriangle.cpp\
screen.cpp\
DownSampler.cpp\
DatasetLoader.cpp\
StreamLine.cpp \
    streamlinegenerator.cpp \
    vectorfieldabstractor.cpp \
    vectorfieldabstractor.cpp \
    VectorFieldAbstractor.cpp \
    Signature.cpp \
    Pair.cpp \
    Sample.cpp \
    featuredetectiondata.cpp \
    FeatureDetector.cpp \
    transformation.cpp \
    cluster.cpp \
    alglib/statistics.cpp \
    alglib/specialfunctions.cpp \
    alglib/solvers.cpp \
    alglib/optimization.cpp \
    alglib/linalg.cpp \
    alglib/interpolation.cpp \
    alglib/integration.cpp \
    alglib/fasttransforms.cpp \
    alglib/diffequations.cpp \
    alglib/dataanalysis.cpp \
    alglib/ap.cpp \
    alglib/alglibmisc.cpp \
    alglib/alglibinternal.cpp \
    drawillustrative.cpp \
    drawillustrativedata.cpp \
    clustercolordialog.cpp \
    clustercolorscheme.cpp \
    seedingideadata.cpp \
    autoseedingdialog.cpp



HEADERS  +=AxisGlyph.h\
Box2.h\
Box3.h\
Camera.h\
CameraPropertyDialog.h\
CameraPropertyModel.h\
CameraPropertyModelDelegate.h\
ColorPickerDialog.h\
CoordinateGrid.h\
CreateBallDialog.h\
CreateBoxDialog.h\
CreateCameraDialog.h\
CreateCylinderDialog.h\
CreateDialog.h\
CustomCursorManager.h\
DirectionalLight.h\
DockWidget.h\
DynamicAction.h\
FixedOrthogonalCamera.h\
GLCanvas.h\
GLSLShader.h\
GLViewport.h\
GlobalProgressBar.h\
GraphicsViewBackground.h\
Light.h\
LightManager.h\
Lin_algebra.h\
Line3.h\
MTRand.h\
MainWindow.h\
Material.h\
Math2.h\
Matrix33.h\
MenuItemWithOptionButton.h\
MultipleView.h\
MultipleViewToolButton.h\
MultiviewBar.h\
MultiviewJoint.h\
OrthogonalCamera.h\
PerspectiveCamera.h\
Plane3.h\
Point2.h\
Point3.h\
PointLight.h\
PropertyDialog.h\
Quaternion.h\
Ray3.h\
Scene.h\
SceneDialog.h\
SceneItem.h\
SceneManagerDialog.h\
SceneManagerModel.h\
Sphere3.h\
SpotLight.h\
StatusbarButton.h\
TempColor.h\
Triangle3.h\
Triangle_Triangle3.h\
UserCameraManager.h\
VectorField.h\
Vertex.h\
base.h\
colorpickerwidget.h\
colorviewer.h\
histogram.h\
intersection3.h\
matrix44.h\
model.h\
point3d.h\
point4.h\
qtcolortriangle.h\
screen.h\
segment3.h\
DownSampler.h\
DatasetLoader.h\
StreamLine.h \
    streamlinegenerator.h \
    vectorfieldabstractor.h \
    vectorfieldabstractor.h \
    VectorFieldAbstractor.h \
    Signature.h \
    Pair.h \
    Sample.h \
    eig3.h \
    featuredetectiondata.h \
    FeatureDetector.h \
    cluster.h \
    transformation.h \
    alglib/statistics.h \
    alglib/specialfunctions.h \
    alglib/solvers.h \
    alglib/optimization.h \
    alglib/linalg.h \
    alglib/interpolation.h \
    alglib/integration.h \
    alglib/fasttransforms.h \
    alglib/diffequations.h \
    alglib/dataanalysis.h \
    alglib/ap.h \
    alglib/alglibmisc.h \
    alglib/alglibinternal.h \
    drawillustrative.h \
    drawillustrativedata.h \
    clustercolordialog.h \
    clustercolorscheme.h \
    seedingideadata.h \
    autoseedingdialog.h

CUDA_SOURCES += cuda.cu
