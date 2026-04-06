#!/bin/bash

BASE="python:3.9-alpine"
COURSE="ikt103"
SOLUTION_IMAGE=$COURSE/test
CONTAINER_NAME=$COURSE-test
ASSIGNMENT="assignment_$1"

# Check for assignment parameter
if [[ "$ASSIGNMENT" = "" ]]; then
    echo "Usage: ./test.sh <assignment>"
    echo "Example: ./test.sh 1"
    echo "Example: ./test.sh 1_1"
    exit 0
fi

# Check for valid assignment name
if ! ls test_$ASSIGNMENT*.py >/dev/null; then
    echo "Error: Failed to find tests for $ASSIGNMENT. Incorrect assignment name?"
    exit 1
fi

# Check for solutions directory
if [[ ! -d "solutions" ]]; then
    echo "Error: Failed to find solutions directory. Incorrect git directory setup?"
    exit 1
fi

# Check for assignment directory
if ! ls solutions/$ASSIGNMENT* >/dev/null; then
    echo "Error: Failed to find $ASSIGNMENT in the solutions directory. Incorrect assignment directory name?"
    exit 1
fi

check()
{
    if [[ $? -eq 0 ]]; then
        echo "$1"
    else
        echo "Error: $2"
        exit 1
    fi
}


# Remove dangling images if there are more than 100 images in total
if [[ $(docker images | wc -l) -gt 100 ]]; then
    echo "Cleaning up Docker..."
    docker image prune -f
    check "Docker cleanup completed successfully." "Failed to complete Docker cleanup."
fi

echo "Looking for base Docker image..."
docker image inspect $BASE >/dev/null 2>&1

if [[ $? -ne 0 ]]; then
    echo "Failed to find base image, downloading..."
    docker pull $BASE
    check "Base image downloaded." "Failed to download base image."
else
    echo "Base image found."
fi

echo "Building solution image..."
docker build . -t $SOLUTION_IMAGE --build-arg ASSIGNMENT=$ASSIGNMENT --build-arg TIMESTAMP="$(date)"
check "Docker solution image built successfully." "Failed to build Docker solution image."

# Cleanup if any signals are received
cleanup()
{
    echo ""
    echo "Signal received, removing containers..."
    docker rm -f $CONTAINER_NAME
    echo "Done."
}

trap cleanup SIGHUP SIGINT SIGTERM

# Git Bash Docker workaround
export MSYS_NO_PATHCONV=1

# Debug info
echo "Docker args: $DOCKER_ARGS"
echo "pytest args: $PYTEST_ARGS"

# Run tests
rm -f results.xml
docker run --rm --init $DOCKER_ARGS --name $CONTAINER_NAME $SOLUTION_IMAGE $PYTEST_ARGS test_$ASSIGNMENT*.py $2 $3 $4 $5 $6 $7
