The project has moved to BitBucket
https://bitbucket.org/Kjems/uversioncontrol

The SVN integration work by encapsulating a command-line version of SVN.

Features:
SVN Window: 
* A status window giving an overview of local files modified, deleted, conflicted etc.
* A line of SVN commands for committing, reverting etc. selected files
* Simple conflict handling
* Dependency check and a suggestion to add dependencies as well

GameObject in inspector:
* Display SVN status of selected resource
* Lock or bypass lock for selected resource by hotkeys, CTRL+L or CTRL+K
* Make a resources readonly if the SVN lock is not acquired

SVN inherent features:
* Branching and merging of project
* Ability to restore a project that crashes Unity

Requirements:
Unity Pro
Commandline SVN client already installed (Mac OSX have one installed by default)


Install:

Step 1:
Windows users download and install a commandline SVN client from here: 
http://www.collab.net/downloads/subversion/
Mac users can skip this step

Step 2:
Follow the instructions for configuring the repository on Unity website:
http://unity3d.com/support/documentation/Manual/ExternalVersionControlSystemSupport.html
Key steps from the guide: 
* Enable external version control under Unity's editor settings. 
* Add your Unity project to SVN, but put ignore on the <projectname>/Library folder.

Step 3:
Make sure the SVN source files are somewhere inside an Editor folder.eg: Assets/Editor/SVN
In Unity under window there is a new window called SVN
In the menu bar there is a item called SVN which contains basic SVN commands
The inspector for GameObject has been modified to include SVN status
Resources locked on SVN are readonly.


Known bugs and limitations:
* The integration does not include a method to enter a login and password, so make sure
  it is cached by making a checkout or update from another SVN client first.
* It is not supported to move folders inside Unity because right now that will 
  result in a nested repository. So move the individual files to a new folder instead.
* There is still no feature to checkout a new repository from inside Unity.


Anyone interested in helping with the development please contact me. 
Especially the GUI classes could use some love.


Contact:
kristian.kjems+UnitySVN@gmail.com