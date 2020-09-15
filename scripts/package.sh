#
# A simple script for building an ipk package out of a project. Please note a specific folder structure is expected:
#
# - project root
#   - build: Must contain the executable and other build artifacts
#   - data: May contain a nested folder structure that will be extracted to the device's root. 
#           This allows including files in the package that will be installed to arbitrary locations on the device.
#   - package: Must contain the res folder, manifest.json and settings.json. 
#              These will be installed to the app's installation folder, same as the executable.
#
# From the project root, invoke this script like so:
# ../scripts/package.sh ./
#
# The first argument must point to your project root.
# 
# As the result of the packaging process, this script will create an ipk file in the dist folder of the project root.
#

function parse_manifest {
    echo $(cat $PROJECT_DIR/package/manifest.json | python3 -c "import sys, json; print(json.load(sys.stdin)['$1'])")
} 

PROJECT_DIR=$1
PROJECT_DIST_DIR=$PROJECT_DIR/dist
PACKAGE_NAME=$(parse_manifest package)
PACKAGE_VERSION=$(parse_manifest version)
INSTALL_DIR=/lametric/data/apps/$PACKAGE_NAME
EXECUTABLE=$(parse_manifest entry)

mkdir $PROJECT_DIST_DIR

echo "Creating debian-binary file..."
echo "2" > $PROJECT_DIST_DIR/debian-binary

echo "Creating control directory..."
mkdir $PROJECT_DIST_DIR/control
cp $PROJECT_DIR/package/manifest.json $PROJECT_DIST_DIR/control/
echo "Package: $PACKAGE_NAME" >> $PROJECT_DIST_DIR/control/control
echo "Version: $PACKAGE_VERSION" >> $PROJECT_DIST_DIR/control/control
echo "Description: " >> $PROJECT_DIST_DIR/control/control
parse_manifest description  >> $PROJECT_DIST_DIR/control/control
echo "Section: admin" >> $PROJECT_DIST_DIR/control/control
echo "Priority: required" >> $PROJECT_DIST_DIR/control/control
echo -n "Maintainer: " >> $PROJECT_DIST_DIR/control/control
parse_manifest vendor  >> $PROJECT_DIST_DIR/control/control
echo "License: GPL" >> $PROJECT_DIST_DIR/control/control
echo "Architecture: arm" >> $PROJECT_DIST_DIR/control/control
echo "Homepage: NA" >> $PROJECT_DIST_DIR/control/control
echo "Source: NA" >> $PROJECT_DIST_DIR/control/control

echo "#!/bin/ash" >> $PROJECT_DIST_DIR/control/postinst
echo "echo 'Creating widget...'" >> $PROJECT_DIST_DIR/control/postinst
echo "/usr/bin/widget.sh create $PACKAGE_NAME" >> $PROJECT_DIST_DIR/control/postinst
chmod +x $PROJECT_DIST_DIR/control/postinst

echo "Creating data directory..."
mkdir $PROJECT_DIST_DIR/data
mkdir -p $PROJECT_DIST_DIR/data/$INSTALL_DIR/
cp -r $PROJECT_DIR/package/* $PROJECT_DIST_DIR/data/$INSTALL_DIR
cp -r $PROJECT_DIR/build/$EXECUTABLE $PROJECT_DIST_DIR/data/$INSTALL_DIR

echo "Copying extra data..."
cp -r $PROJECT_DIR/data/* $PROJECT_DIST_DIR/data

echo "Packaging up..."
pushd $PROJECT_DIST_DIR/control
tar --numeric-owner --group=0 --owner=0 -czf ../control.tar.gz ./*
popd
pushd $PROJECT_DIST_DIR/data
tar --numeric-owner --group=0 --owner=0 -czf ../data.tar.gz ./*
popd
pushd $PROJECT_DIST_DIR
ar r ${PACKAGE_NAME}_${PACKAGE_VERSION}.ipk ./debian-binary ./data.tar.gz ./control.tar.gz 
popd

rm -r $PROJECT_DIST_DIR/control
rm -r $PROJECT_DIST_DIR/data
rm -r $PROJECT_DIST_DIR/debian-binary

rm $PROJECT_DIST_DIR/data.tar.gz
rm $PROJECT_DIST_DIR/control.tar.gz
