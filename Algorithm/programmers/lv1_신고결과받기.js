function solution(id_list, report, k) {

  let answer = []

  for (let i=0; i<id_list.length; i++) {
    answer.push(0)
  }

  let process_obj = {}  

  id_list.map(item => {
    process_obj[item] = []
  })

  report.map(item => {
    newArr = item.split(" ")
    if (!process_obj[newArr[1]].includes(newArr[0])){
      process_obj[newArr[1]].push(newArr[0])
    }
  })

  for (let key in process_obj) {
    if (process_obj[key].length >= k) {
      for (let i=0; i<process_obj[key].length; i++) {
        answer[id_list.indexOf(process_obj[key][i])]++
      }
    }
  }

  return answer
}