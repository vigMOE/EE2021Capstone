init of the sound board branch, for use to transmit game state to robot at the begining of the match.

current idea is to utilize a start signal, 6 On/off intermediate signals, and an end signal


to switch branches

	git checkout Branch_Name


to add all files from your local machine to local git

	git add -A


to commit changes from local to "ready to push"

	git commit


set push upstream (So git knows where to push your directory)

	git push --set-upstream origin Branch_Name


push changes 

	git push origin Branch_Name


push changes to master

	git push origin Local_Branch_Name:master


pull changes from Branch_Name to the branch you are currently checked out on

	git pull Branch_Name


command sequence to push after editing

	git add -A

	git commit -m "Commit Message"

	git push origin Branch_Name

<<<<<<< HEAD
this is a backup incase someone overrides the master branch 
=======

>>>>>>> ae509c54fa61b22cf1c20fc471033298b36cea6c
