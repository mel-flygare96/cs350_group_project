#cs350_group_project

##Compilation and Execution
1. To compile the randGenerator, run `make randGen`
2. To compile the tests, run `make randTest`
3. To compile both, run `make all`
4. To run randGen, execute `./randGen.exe`
5. To run randTest, run `./randTest.exe`

##Git Basics
1. Follow this guide to generate an ssh key and add it to your github account: https://help.github.com/articles/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent/
1. (Alt) If you do not want to deal with the ssh key, use `git clone https://github.com/mel-flygare96/cs350_group_project.git`. This is easier than using ssh, but every
time you push or pull, you will need to re-enter your github credentials. Annoying.
2. type `git clone git@github.com:mel-flygare96/cs350_group_project.git`. This will clone the repository into a folder called cs350_group_project
3. When you are ready to commit code, first type `git status`. This will show all current changes, tracked and untracked. You can add files directly to the commit,
or add all files at once. The .gitignore included with this project should keep any unwanted files from commiting, so you can just run `git add -A`.
4. If you type `git status` again, you should see no changes.
5. Type `git commit -m "enter your commit message here"`. This will commit the changes to your local repository. These will not reflect on the remote repo.
6. Type `git fetch` at any point to retrieve changes from the remote branch. This will update your local repository to match the structure of the remote repo, but it will not
update your code to match. If there are code changes in the files you are working in, you MUST pull the changes before pushing your code. Run `git push`. After the push, you may
need to commit.
7. You can make multiple commits before pushing code. When you are ready to push code, first run `git fetch` and `git pull`, then type `git push origin master`. You may have to 
set an upstream branch (it will tell you). If you do need to, follow the instructions it gives. This should allow you to just use `git push` after that.
