## EterAPP
This doc describes the code of the app that suscribes (client) to the mosquitto broker in the server, and stores the measurements in the database. This requires to have postgresql installed and have created eter database (to be continued).
## Install the components from Debian/Ubuntu repositories

The first step will be to update the repositories and install pip3 by typing:

`
sudo apt install update  
sudo apt install python-pip3
`

Next we will install virtualenv using pip

`sudo pip install virtualenv
`

Now creat a directory for our Flask project.

`
mkdir ~/api  
cd ~/api
`

Next, clone the repository by typing:

`
git clone 
`
Move into folder **src_api** and create a folder **venv**, where we install the requeriment typing:

`
src_api$ virtualenv venv  
src_api$ venv/bin/pip install -r requeriments.txt
`
Now, run the project with

`
src_api$ venv/bin/python run.py
`
