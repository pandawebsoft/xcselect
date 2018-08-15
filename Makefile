BUILD_VERSION=$(shell git rev-list HEAD | wc -l | tr -d ' ')

all:
	@ make compile
	@ make install
	
compile:
	@ make update-version-number

	@ echo "Compiling..."
	@ gcc xcselect.c -o ./bin/xcselect
	@ echo "Done."

install:
	@ echo "Installing..."
	@ cp -f ./bin/xcselect /usr/local/bin/
	@ echo "Done."

update-version-number:
	$(eval version = $(shell cat ./version)(${BUILD_VERSION}))
	@ sed -i "" "s~#define VERSION \"[0-9.()]*\"~#define VERSION \"$(version)\"~" ./xcselect.c

