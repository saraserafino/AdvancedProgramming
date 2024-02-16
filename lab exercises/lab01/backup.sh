#!/bin/bash

#receive the directory to backup
read -p 'Which directory do you want to backup?' input_directory

#check if the directory exists
while [ ! -d "$input_directory" ]
do
echo "That is not a directory."
read -p ' Which one do you want to backup?' input_directory
done

output_directory="${HOME}/backup"
#if it does not exist create it
mkdir -p ${output_directory}

#extract the last part of the directory name with basename
#for example if we have /home/user/Documents, basename is Documents
directory_name=$(basename ${input_directory})

#Generate the timestamped backup directory name
backup_directory=${directory_name}_$(date +%Y%m%d_%H%M%S)

echo "Copying to backup folder..."
cp -r ${input_directory} ${output_directory}/${backup_directory}

echo "Creating backup archive..."
#save and change to output_directory
#dev/null is an empty file where you put things you don't want to see
pushd $output_directory > /dev/null

#create a tar archive where c compress, z is the gzip file format, f specifies the output file
#.tar.gz compress the backup_directory into a single archive file
tar czf ${backup_directory}.tar.gz $backup_directory

#print ending of backup
echo "Backup finished"

#go back to the original folder
popd > /dev/null
