#!/bin/sh
# Select the docker file depending on wanted target keyword

declare -A dockerfiles=(
    ["software"]="dockerfiles/software"
    ["arm"]="dockerfiles/arm"
)

name="$1"

# If no name is specified
if [[ -z "$name" ]]; then
    echo "Copy the wanted target Dockerfile to build."
    echo "Usage: $0 <name>"
    exit 1
fi

# If there is a name
if [[ -v "dockerfiles[$name]" ]]; then
    dockerfile="${dockerfiles[$name]}"

    echo "Copy '$dockerfile' as 'Dockerfile'."

    # Copy the dockerfile in current directory
    cp $dockerfile Dockerfile

    echo "Done."

# There is not this spectified keyword
else
    echo "Unknown '$name' keyword."
    exit 1
fi
