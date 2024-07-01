import random
from datetime import datetime, timedelta

def generate_random_datetimes(start_date, end_date):
    # 将开始和结束日期转换为datetime对象
    start_datetime = datetime.strptime(start_date, "%Y-%m-%d %H:%M:%S")
    end_datetime = datetime.strptime(end_date, "%Y-%m-%d %H:%M:%S")

    # 计算时间范围
    time_range = end_datetime - start_datetime

    # 随机生成两个时间差
    random_time_delta1 = random.randint(0, time_range.total_seconds())

    random_time_delta12 = random.randint(10800, 68400)

    # 计算随机时间
    random_datetime1 = start_datetime + timedelta(seconds=random_time_delta1)
    random_datetime2 = random_datetime1 + timedelta(seconds=random_time_delta12)

    return random_datetime1, random_datetime2

def random_flight():
    # 定义开始和结束日期
    start_date = "2010-09-01 08:30:00"
    end_date = "2012-06-20 18:45:00"
    # 生成随机时间并输出
    datetime1, datetime2 = generate_random_datetimes(start_date, end_date)

    random_startpos="pos"+str(random.randint(1,200))
    random_endpos="pos"+str(random.randint(1,200))

    random_type=random.randint(1,10)
    random_price=round(random.random()*2000 + 300,2)

    res=random_startpos+'\t\t'+random_endpos+'\t\t'+datetime1.strftime("%Y-%m-%d %H:%M:%S")+'\t\t'+datetime2.strftime("%Y-%m-%d %H:%M:%S")+'\t\t'+str(random_type)+'\t\t'+str(random_price)
    return res

with open('info.txt','w') as file:
    for i in range(0,2001):
        info=str(i)+'\t\t'+random_flight()+'\n'
        file.write(info)