from db import db
from sqlalchemy import text


class Employees(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(20), nullable=False)
    surname = db.Column(db.String(50), nullable=False)
    salary = db.Column(db.Integer, nullable=False)

    def __repr__(self):
        return f"{self.id} + {self.name} + {self.surname} + {self.salary}"

    def save(self):
        db.session.add(self)
        db.session.commit()

    def delete(self):
        db.session.delete(self)
        db.session.commit()
    @staticmethod
    def sql_query(query: str):
        db.session.execute(text(query))
        db.session.commit()
