import psycopg2 as pg
import sys

class DB:
  def __init__(self, host, db, user, pwd):
    self.host = host
    self.db = db
    self.user = user
    self.pwd = pwd
    self.con = None

  def connect(self):
    try:
      # Setup DB Connection
      self.con = pg.connect(
        "host='%s' dbname='%s' user='%s' password='%s'" %
        (self.host, self.db, self.user, self.pwd)
      )
      print('DB connection established')

    except pg.DatabaseError as e:
      if self.con:
        self.con.rollback()

      print('DB Error %s' % e)
      self.exit()

  def query(self, q, params):
    try:
      with self.con.cursor() as curs:
        curs.execute(q, params)
        self.con.commit()
    except Exception as e:
      t = type(e)
      print("Error executing SQL: %s %s %s" % (t.__module__, t.__name__, e))
      self.con.rollback()
      raise e

  def exit(self):
    print('Exiting')
    if self.con:
      self.con.close()
    sys.exit(1)
