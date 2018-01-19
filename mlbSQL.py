"""
CS181: Project 2: Relational Databases
Hayley LeBlanc and John Fernow
October 2017
"""
# setup
from sqlalchemy import create_engine, Table, MetaData, select, func, distinct, and_, or_
import pandas as pd
import keys
protocol = "mysql+mysqlconnector"
userid = keychain['mysql']['userid']
userpass = keychain['mysql']['userpass']
mysqlhost = "hadoop2.mathsci.denison.edu"
database = "lahman2016"
connectionstring = "{}://{}:{}@{}/{}".format(protocol, userid, userpass, mysqlhost, database)

engine = create_engine(connectionstring)
metadata = MetaData()
#===========================================================
# create the necessary tables for the SQL Alchemy statements to use later
master = Table("Master", metadata, autoload=True, autoload_with=engine)
batting = Table("Batting", metadata, autoload=True, autoload_with=engine)
salaries = Table("Salaries", metadata, autoload=True, autoload_with=engine)
teams = Table("Teams", metadata, autoload=True, autoload_with=engine)
#===========================================================
def q1():
    # Question: Does a player's height and weight affect their career batting average?
    #Raw SQL:
    """
    SELECT Master.playerID, Master.nameFirst, Master.nameLast, Master.weight, Master.height, 
    AVG(Batting.H/Batting.AB) AS BattingAverage
    FROM (Master
        INNER JOIN Batting
        ON Master.playerID = Batting.playerID)
    WHERE Master.weight <> 0 AND
            Master.weight IS NOT NULL AND
            Master.height <> 0 AND
            Master.height IS NOT NULL AND
            Batting.AB <> 0
            Batting.H IS NOT NULL AND
            Batting.AB IS NOT NULL
    GROUP BY Master.playerID
    ORDER BY Master.nameLast;
    """

    # SQL Alchemy
    with engine.connect() as connection:
        stmt = select([master.c.playerID, master.c.weight, master.c.height, \
                      func.avg(batting.c.H/batting.c.AB).label("BattingAverage")])
        stmt = stmt.select_from(master.join(batting, master.c.playerID==batting.c.playerID))
        stmt = stmt.where(and_(master.c.weight != 0, master.c.weight != None))
        stmt = stmt.where(and_(master.c.height != 0, master.c.height != None))
        stmt = stmt.where(batting.c.AB != 0)
        stmt = stmt.where(and_(batting.c.H != None, batting.c.AB != None))
        stmt = stmt.group_by(master.c.playerID)
        stmt = stmt.order_by(master.c.playerID)
        df = pd.read_sql_query(stmt, engine)
        # set the DataFrame's index to get rid of the automatically generated index column
        df = df.set_index(["playerID"])
        
    df.to_csv("question1.csv")
    df.head(10)
q1()
#===========================================================
def q2():
    # Question: Which states do the highest-paid baseball players come from?

    # Raw SQL:
    """
    SELECT Master.playerID, AVG(Salaries.salary) AS AverageSalary, Master.birthState
        FROM (Master
            INNER JOIN Salaries
            ON Master.playerID = Salaries.playerID)
        GROUP BY Master.playerID
    """

    # SQL Alchemy
    with engine.connect() as connection:
        stmt1 = select([master.c.playerID, func.avg(salaries.c.salary).label("AvgSalary"), master.c.birthState])
        stmt1 = stmt1.select_from(master.join(salaries, master.c.playerID==salaries.c.playerID))
        stmt1 = stmt1.group_by(master.c.playerID)

        df1 = pd.read_sql_query(stmt1, engine)
        # set the DataFrame's index to get rid of the automatically generated index column
        df1 = df1.set_index(["playerID"])
        
    df1.to_csv("question2_1.csv")
    df1.head(10)
q2()
#===========================================================
def q3():
    # Question: Which countries do the highest-paid baseball players come from?

    # Raw SQL:
    # SELECT Master.playerID, AVG(Salaries.salary) AS AverageSalary, Master.birthCountry
    #    FROM (Master
    #        INNER JOIN Salaries
    #        ON Master.playerID = Salaries.playerID)
    #    GROUP BY Master.playerID

    # SQL Alchemy
    with engine.connect() as connection:
        stmt2 = select([master.c.playerID, func.avg(salaries.c.salary).label("AverageSalary"), master.c.birthCountry])
        stmt2 = stmt2.select_from(master.join(salaries, master.c.playerID==salaries.c.playerID))
        stmt2 = stmt2.group_by(master.c.playerID)

        df2 = pd.read_sql_query(stmt2, engine)
        # set the DataFrame's index to get rid of the automatically generated index column
        df2 = df2.set_index(["playerID"])
        
    df2.to_csv("question2_2.csv")
    df2.head(10)
q3()
#===========================================================
def q4():
    # Question: Do teams in the American League have higher average batting averages than teams in the National League?

    # Raw SQL:
    # SELECT Teams.teamID, Teams.name, Teams.lgID, AVG(Batting.H/Batting.AB) AS AvgBattingAverage
    #    FROM (Teams
    #        INNER JOIN Batting
    #        ON Teams.teamID = Batting.teamID)
    #    WHERE Batting.AB <> 0 AND
    #        Batting.H IS NOT NULL AND
    #        Batting.AB IS NOT NULL AND
    #        (Teams.lgID = 'AL' OR Teams.lgID = 'NL)
    #    GROUP BY Teams.teamID
    #    ORDER BY Teams.lgID;

    # SQLAlchemy
    with engine.connect() as connection:
        stmt = select([teams.c.teamID, teams.c.name, teams.c.lgID, \
                       func.avg(batting.c.H/batting.c.AB).label("AvgBattingAverage")])
        stmt = stmt.select_from(teams.join(batting, teams.c.teamID==batting.c.teamID))
        stmt = stmt.where(and_(batting.c.AB != 0, batting.c.H != None))
        stmt = stmt.where(batting.c.AB != None)
        stmt = stmt.where(or_(teams.c.lgID=="AL", teams.c.lgID=="NL"))
        stmt = stmt.where(teams.c.yearID >= 1973)
        stmt = stmt.group_by(teams.c.teamID)
        stmt = stmt.order_by(teams.c.lgID)

        df = pd.read_sql_query(stmt, engine)
        # set the DataFrame's index to get rid of the automatically generated index column
        df = df.set_index(["teamID"])
        
    df.to_csv("question3.csv")
    df.head(10)
q4()
#===========================================================
def q6():
    # Question: Do teams with higher ranks get significantly higher attendance? (in 2016)

    Teams = Table('Teams',metadata,autoload=True, autoload_with=engine)
    rawSQL = """
    SELECT DISTINCT teamID, attendance, rank
    FROM Teams
    WHERE attendance > 0 AND yearID = 2016
    GROUP BY teamID;
    """
    
    with engine.connect() as connection:
        stmt = select([Teams.c.teamID,
                       Teams.c.attendance,
                       Teams.c.Rank])
        
        stmt = stmt.distinct()
        
        stmt = stmt.where(Teams.c.attendance > 0)
        
        stmt = stmt.where(Teams.c.yearID == 2016)
        
        results = connection.execute(stmt).fetchall()
        df = pd.DataFrame(results)
        df.columns = results[0].keys()
        
    # exported to CSV to use in Tableau
    df.to_csv('attendance.csv',index=False)

    df.head(10)
q6()    
#===========================================================
def q7():
    # Question: If teams pay their best players more, do they have more players in the Hall of Fame?

    HallOfFame = Table('HallOfFame',metadata,autoload=True, autoload_with=engine)
    Salaries = Table('Salaries',metadata,autoload=True, autoload_with=engine)

    rawSQL = """
    SELECT DISTINCT HallOfFame.playerID, Salaries.salary, Salaries.teamID
    FROM HallOfFame
    INNER JOIN Salaries ON HallOfFame.playerID = Salaries.playerID;
    """

    with engine.connect() as connection:
        stmt = select([HallOfFame.c.playerID,
                       Salaries.c.salary,
                       Salaries.c.teamID])
        
        stmt = stmt.select_from(
            HallOfFame.join(Salaries, HallOfFame.c.playerID == Salaries.c.playerID)
        )
        
        stmt = stmt.distinct()
        
        results = connection.execute(stmt).fetchall()
        df = pd.DataFrame(results)
        df.columns = results[0].keys()
        
    # exported to CSV to use in Tableau
    df.to_csv('hall_of_fame.csv',index=False)
        
    df.head(10)
q7()
#===========================================================
q8():
    # Question: Are player managers better than non-player managers?

    Managers = Table('Managers',metadata,autoload=True, autoload_with=engine)

    rawSQL = """
    SELECT DISTINCT playerID, plyrMgr, Rank
    FROM Managers;
    """

    with engine.connect() as connection:

        stmt = select([Managers.c.playerID,
                       Managers.c.plyrMgr,
                       Managers.c.rank])
        
        stmt = stmt.distinct()
        
        results = connection.execute(stmt).fetchall()
        df = pd.DataFrame(results)
        df.columns = results[0].keys()
        
    # exported to CSV to use in Tableau
    df.to_csv('managers.csv',index=False)
        
    df.head(10)
q8()    
