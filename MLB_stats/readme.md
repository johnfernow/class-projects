# Analyzing Major League Baseball statistics
To view the project, you can either open the `.ipynb` file (if you have
Jupyter) located in the `full_project` directory or open `MLB_stats.pdf`.

In order to fully replicate the results of this program or make modifications,
you will have to set-up an SQL server (a local server is fine) and create a
keychain to connect to it. You'll have to modify part of the notebook to connect
to your server instead of the server I listed (it is no longer online). You will
also have to find and import Sean Lahman’s public database of MLB stats.

If you are only interested in the source code of the project, without its
output and visualizations, you can view `mlbSQL.py` (but it won't run correctly
since the server is no longer online — viewing the `.ipynb` will display the
correct output since I have included the .ipynb checkpoints).

Note, the program contains both raw SQL and SQL Alchemy. The raw SQL is never
actually ran, but was just present to display that we understood it as well as
SQL Alchemy.
