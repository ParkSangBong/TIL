-- 코드를 입력하세요
SELECT HOUR(DATETIME) as DATETIME, COUNT(DATETIME) as COUNT 
FROM animal_outs 
GROUP BY HOUR(DATETIME) HAVING DATETIME >= 9 AND DATETIME <= 19 
order by HOUR(datetime)