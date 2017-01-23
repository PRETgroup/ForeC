#!/bin/bash

#  Created by Alex Karahalios on 6/12/11
#  Edited by Brian Reinhart on 08/02/2012 .
#  Last edited 8/02/2012
#
# Updates Xcode and to support ForeCast language for editing
#

# Path were this script is located
#
SCRIPT_PATH="$(dirname "$BASH_SOURCE")"

# Set up path for PlistBuddy helper application which can add elements to Plist files
#
PLISTBUDDY=/usr/libexec/PlistBuddy

# This framework is found withing the Xcode.app package and is used when Xcode is a monolithic
# install (all contained in Xcode.app)
#
DVTFOUNDATION_PATH="/Applications/Xcode.app/Contents/SharedFrameworks/DVTFoundation.framework/Versions/A/Resources/"

# Create Plist file of additional languages to add to 'DVTFoundation.xcplugindata'
#
cat >AdditionalLanguages.plist <<EOF
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>Xcode.SourceCodeLanguage.ForeCast</key>
	<dict>
		<key>languageSpecification</key>
		<string>xcode.lang.forecast</string>
		<key>fileDataType</key>
		<array>
			<dict>
				<key>identifier</key>
				<string>public.forecast-source</string>
			</dict>
		</array>
		<key>id</key>
		<string>Xcode.SourceCodeLanguage.ForeCast</string>
		<key>point</key>
		<string>Xcode.SourceCodeLanguage</string>
		<key>languageName</key>
		<string>ForeCast</string>
		<key>version</key>
		<string>1.0</string>
		<key>conformsTo</key>
		<array>
			<dict>
				<key>identifier</key>
				<string>Xcode.SourceCodeLanguage.Generic</string>
			</dict>
		</array>
		<key>name</key>
		<string>ForeCast Language</string>
	</dict>
</dict>
</plist>
EOF

# Now merge in the additonal languages to DVTFoundation.xcplugindata
#
$PLISTBUDDY "$DVTFOUNDATION_PATH/DVTFoundation.xcplugindata"  -c 'Merge AdditionalLanguages.plist plug-in:extensions'

# Get rid of the AdditionalLanguages.plist since it was just temporary
#
rm -f AdditionalLanguages.plist

# Copy in the xclangspecs for the languages (assumes in same directory as this shell script)
#
cp "$SCRIPT_PATH/ForeCast.xclangspec" "$DVTFOUNDATION_PATH"

# Remove any cached Xcode plugins
#
rm -f /private/var/folders/*/*/*/com.apple.DeveloperTools/*/Xcode/PlugInCache.xcplugincache
