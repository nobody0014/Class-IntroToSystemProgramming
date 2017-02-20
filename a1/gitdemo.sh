#!/bin/bash
git init --bare /subm/u5780995/git_demo
git clone /subm/u5780995/git_demo ./git_demo_1
touch ./git_demo_1/hello.world
cd git_demo_1
git add -A 
git commit -am "initial commit"
git push
cd ..
git clone /subm/u5780995/git_demo ./git_demo_2
cd git_demo_2
echo "u5780995" > hello.world
git add -A 
git commit -am "initial commit"
git push
cd ..
cd git_demo_1
git pull
echo "file content: " `cat hello.world`
cd ..




