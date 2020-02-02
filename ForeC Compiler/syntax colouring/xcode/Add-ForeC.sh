#!/bin/bash

#  Created by Alex Karahalios on 6/12/11
#  Edited by Brian Reinhart on 08/02/2012 .
#  Last edited 8/02/2012
#
# Updates Xcode and to support ForeC language for editing
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
	<key>Xcode.SourceCodeLanguage.ForeC</key>
	<dict>
		<key>commentSyntax</key>
		<array>
			<dict>
				<key>prefix</key>
				<string>/*</string>
				<key>suffix</key>
				<string>*/</string>
			</dict>
			<dict>
				<key>prefix</key>
				<string>//</string>
			</dict>
		</array>
		<key>conformsTo</key>
		<array>
			<dict>
				<key>identifier</key>
				<string>Xcode.SourceCodeLanguage.Generic</string>
			</dict>
		</array>
		<key>languageSpecification</key>
		<string>xcode.lang.forec</string>
		<key>documentationAbbreviation</key>
		<string>forec</string>
		<key>fileDataType</key>
		<array>
			<dict>
				<key>identifier</key>
				<string>public.forec-source</string>
			</dict>
		</array>
		<key>id</key>
		<string>Xcode.SourceCodeLanguage.ForeC</string>
		<key>point</key>
		<string>Xcode.SourceCodeLanguage</string>
		<key>languageName</key>
		<string>ForeC</string>
		<key>version</key>
		<string>1.0</string>
		<key>name</key>
		<string>ForeC Language</string>
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
cp "$SCRIPT_PATH/ForeC.xclangspec" "$DVTFOUNDATION_PATH"

# Remove any cached Xcode plugins
#
rm -f /private/var/folders/*/*/*/com.apple.DeveloperTools/*/Xcode/PlugInCache.xcplugincache
