CPP = g++
INC = -I../cryphutil -I../fontutil -I../glslutil -I../mvcutil -I../imageutil
C_FLAGS = -fPIC -g -c -DGL_GLEXT_PROTOTYPES $(INC)

LINK = g++ -fPIC -g
LOCAL_UTIL_LIBRARIES = -L../lib -lcryph -lfont -lglsl -lmvc -limage
OGL_LIBRARIES = -lglfw -lGLU -lGL

OBJS = project4.o ModelViewWithLighting.o getMatrices.o Controller_Subclass.o Court.o Block.o Basketball_Goal.o Disk.o Bleachers.o Bench.o Bench_Top.o Background.o Fence_top.o Fence_side.o Tex_backboard.o Tex_backboard_flip.o

project4: $(OBJS) ../lib/libcryph.so ../lib/libfont.so ../lib/libglsl.so ../lib/libmvc.so ../lib/libimage.so
	$(LINK) -o project4 $(OBJS) $(LOCAL_UTIL_LIBRARIES) $(OGL_LIBRARIES)

../lib/libcryph.so: ../cryphutil/AffVector.h ../cryphutil/AffVector.c++ ../cryphutil/AffPoint.h ../cryphutil/AffPoint.c++
	(cd ../cryphutil; make)

../lib/libfont.so: ../fontutil/CFont.h ../fontutil/CFont.c++ ../fontutil/CGLString.h ../fontutil/CGLString.c++
	(cd ../fontutil; make)

../lib/libglsl.so: ../glslutil/ShaderIF.h ../glslutil/ShaderIF.c++
	(cd ../glslutil; make)

../lib/libmvc.so: ../mvcutil/Controller.h ../mvcutil/Controller.c++ ../mvcutil/ModelView.h ../mvcutil/ModelView.c++
	(cd ../mvcutil; make)

../lib/libimage.so: ../imageutil/ImageReader.h ../imageutil/ImageReader.c++
	(cd ../imageutil; make)

project4.o: project4.c++
	$(CPP) $(C_FLAGS) project4.c++
getMatrices.o: getMatrices.c++
	$(CPP) $(C_FLAGS) getMatrices.c++
ModelViewWithLighting.o: ModelViewWithLighting.h ModelViewWithLighting.c++
	$(CPP) $(C_FLAGS) ModelViewWithLighting.c++
Controller_Subclass.o: Controller_Subclass.h Controller_Subclass.c++
	$(CPP) $(C_FLAGS) Controller_Subclass.c++
Court.o: Court.h Court.c++
	$(CPP) $(C_FLAGS) Court.c++
Block.o: Block.h Block.c++
	$(CPP) $(C_FLAGS) Block.c++
Basketball_Goal.o: Basketball_Goal.h Basketball_Goal.c++
	$(CPP) $(C_FLAGS) Basketball_Goal.c++
Disk.o: Disk.h Disk.c++
	$(CPP) $(C_FLAGS) Disk.c++
Bench.o: Bench.h Bench.c++
	$(CPP) $(C_FLAGS) Bench.c++
Bench_Top.o: Bench_Top.h Bench_Top.c++
	$(CPP) $(C_FLAGS) Bench_Top.c++
Bleachers.o: Bleachers.h Bleachers.c++
	$(CPP) $(C_FLAGS) Bleachers.c++
Background.o: Background.h Background.c++
	$(CPP) $(C_FLAGS) Background.c++
Fence_top.o: Fence_top.h Fence_top.c++
	$(CPP) $(C_FLAGS) Fence_top.c++
Fence_side.o: Fence_side.h Fence_side.c++
	$(CPP) $(C_FLAGS) Fence_side.c++
Backboard.o: Backboard.h Backboard.c++
	$(CPP) $(C_FLAGS) Backboard.c++
Tex_backboard.o: Tex_backboard.h Tex_backboard.c++
	$(CPP) $(C_FLAGS) Tex_backboard.c++
Tex_backboard_flip.o: Tex_backboard_flip.h Tex_backboard_flip.c++
	$(CPP) $(C_FLAGS) Tex_backboard_flip.c++