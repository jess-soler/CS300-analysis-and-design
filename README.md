# CS300-analysis-and-design
Final Project

- ### What was the problem you were solving in the projects for this course?
The problem I was solving in this course was the development of an advising assistance software tool for the Computer Science department at ABC University (ABCU). The goal of this project was to help academic advisors efficiently manage and access course information while assiting students.  The software needed to read and process course data from a CSV file.  This required parsing each line into course objects and validating the data.  The project also required selecting and implementing an efficient data structure to store and retreive course informaiton.  I evaluated vectors, hash tables, and binary search trees.  The binary search tree was chosen because it provided efficiency and allowed storing the courses in alphanumeric order.  
  
- ### How did you approach the problem? Consider why data structures are important to understand.
I focused on aligning functional requirements with computational efficiency.  The goal was to store data in a data structure that optimized both searching and alphanumeric sorting.  I began iwth requirement analysis and data modeling by defining a Course structure to encapsulate relevant information from the CSV file.  Additionally, I evaluated the three data structures for efficiency.  The vector was simple and memory efficient but requried linear searches.  The hash table provided fast lookups, but didn't maintain order which decreased efficiency during printing.  The binary search tree offered a balanced solution with an average search time of O(log n) and the ability to maintain data in sorted order.  I implemented the binary search tree with recursive insertion, iterative search logic, and in order traversal to print courses.  Understanding these data structures directly influenced the algorithms used for searching, inserting, and sorting.  Understanding Big-O notaiton helped highlight how performance differences become significant as data size increases.
  
- ### How has your work on this project expanded your approach to designing software and developing programs?
Working on this project shifted my focus from making code function correctly to evaluatiung the computational efficiency and scalability of different solutions.  Instead of choosing the first working approach, I learned to analyze how well a solution performs as the size of the dataset increases.  
  
- ### How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
This project has expanded my ability to create scalable and high performing software through the design process.  I now use Big-O analysis to guide decisions in development.  
