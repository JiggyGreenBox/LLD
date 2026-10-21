/*
Problem 2: Student Gradebook

SDE1 · Beginner

Problem statement

Design and implement a Student Gradebook system in C++ that manages 
students, their course grades, and their academic performance.
The system should allow students to be registered, grades to be 
recorded for courses, and grade statistics to be calculated.

Requirements

    1. Student: Each student has a unique ID, name, and a collection of 
    grades.
    2. Register student: Add a student to the gradebook. Reject duplicate 
    student IDs.
    3. Record grade: Add a grade for a particular course for an existing 
    student.
    4. Update grade: Change a student's grade for a course if a grade has 
    already been recorded.
    5. Calculate average: Calculate the average grade for a student 
    across their recorded courses.
    6. View student: Display a student's ID, name, grades, and average.
    7. Class average: Calculate the average of all recorded grades across 
    all students.
    8. Validation: Reject grades outside the range 0–100. Handle 
    attempts to access or update grades for nonexistent students or 
    courses.
    9. Empty gradebook: Handle students with no grades and a gradebook 
    with no students without dividing by zero.


Example
Suppose the gradebook contains:
    Student	Course	    Grade
    Alice	Mathematics	85
    Alice	Physics	    90
    Bob	    Mathematics	70
    Bob	    Physics	    80
Expected results:
- Alice's average: (85 + 90) / 2 = 87.5
- Bob's average: (70 + 80) / 2 = 75
- Class average: (85 + 90 + 70 + 80) / 4 = 81.25

Constraints
- Use in-memory data structures; no database.
- A course is identified by its name for this exercise.
- Each student can have at most one grade per course.
- Use double for averages.
- A student with no grades has no defined average. Choose a 
consistent way to represent this, such as std::optional<double>.
*/

/*
student
    student_id
    student_name

course
    course_id
    course_name

coursescore
    course_id
    student_id
    score    

gradebook

    students    <id, student> 
    courses     <id, course>
    scores      <id, coursescores> 
    

    register_student( student )

    register_course( course )

    gradeStudent( coursescore )

    getCourseAverage( course_id )

    getStudentAverage( student_id )

    getAllAverages()
*/

#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>
#include <optional>
using namespace std;


class Student {
private:
    int student_id;
    string student_name;
public:
    Student(int id, string name) :student_id(id), student_name(name) {}

    int id() const {
        return student_id;
    }
};
    


class Course {
private:
    int course_id;
    string course_name;
public:
    Course(int id, string name) :course_id(id), course_name(name) {}

    int id() const {
        return course_id;
    }
};
    

class CourseScore {
private:
    string combined_id;
    int course_id;
    int student_id;
    int  score;
public:
    CourseScore(int cid, int sid, int score) :course_id(cid), student_id(sid), score(score) {
        combined_id = to_string(student_id) + ":" + to_string(course_id); 
    }

    int getScore() const {
        return score;
    }

    void updateScore(int _score) {
        score = _score;
    }

    string getCombinedId() const {
        return combined_id;
    }

    int getCourseId() const {
        return course_id;
    }

    int getStudentId() const {
        return student_id;
    }
};

class Gradebook {
private:
    unordered_map<int, Student>  students;
    unordered_map<int, Course> courses;
    unordered_map<string, CourseScore>  scores;

public:
    

    bool register_student( Student student ) {
        auto it = students.find(student.id());
        if(it != students.end()) 
            return false;

        students.emplace(student.id(), student);
        return true;
    }

    bool register_course( Course  course) {
        auto it = courses.find(course.id());
        if(it != courses.end()) 
            return false;

        courses.emplace(course.id(), course);
        return true;
    }

    bool gradeStudent( CourseScore coursescore ) {
        int score = coursescore.getScore();

        if(score < 0 || score > 100)
            return false;

        // is student valid
        if (students.find(coursescore.getStudentId()) == students.end())
            return false;

        // is course valid
        if (courses.find(coursescore.getCourseId()) == courses.end())
            return false;

        string course_id = coursescore.getCombinedId(); // student + course is unique
        auto it = scores.find(course_id);
        if(it != scores.end()) {
            it->second.updateScore(score);
            return true;
        }

        scores.emplace(course_id, coursescore);
        return true;
    }

    optional<double> getCourseAverage( int course_id ) {
        // validate course_id
        auto it = courses.find(course_id);
        if(it == courses.end())
            return nullopt;

        int n = 0;
        double total = 0;
        for(const auto &[id, course_score] : scores) {
            if(course_score.getCourseId() == course_id) {
                n++;
                total += course_score.getScore();
            }
        }

        if (n == 0)
            return nullopt;

        return total / n;
    }

    
    optional<double> getStudentAverage( int student_id ) {
        // validate student_id
        auto it = students.find(student_id);
        if(it == students.end())
            return nullopt;

        int n = 0;
        double total = 0;
        for(const auto &[id, course_score] : scores) {
            if(course_score.getStudentId() == student_id) {
                n++;
                total += course_score.getScore();
            }
        }

        if (n == 0)
            return nullopt;

        return total / n;
    }

    double getAllAverages() {
        int n = 0;
        double total = 0;
        for(const auto &[id, course_score] : scores) {            
            n++;
            total += course_score.getScore();            
        }
        return (n==0) ? 0 : total / n;
    }
};


    


int main() {

    Gradebook book;
    Student s1(1, "sourabh");
    Student s2(2, "jiggy");
    Student s3(3, "abc");


    Course c1(1, "math");
    Course c2(2, "sci");
    Course c3(3, "hist");

    book.register_student(s1);
    book.register_student(s2);
    book.register_student(s3);

    book.register_course(c1);
    book.register_course(c2);
    book.register_course(c3);


    book.gradeStudent(CourseScore(c1.id(), s1.id(), 50));
    book.gradeStudent(CourseScore(c1.id(), s2.id(), 60));
    book.gradeStudent(CourseScore(c1.id(), s3.id(), 70));

    
    auto avg = book.getCourseAverage(c1.id());
    if (avg.has_value())
        cout << avg.value() << endl;
    else
        cout << "no scores recorded for this course" << endl;
        
    cout << book.getAllAverages() << endl;

    book.gradeStudent(CourseScore(c2.id(), s1.id(), 40));
    book.gradeStudent(CourseScore(c2.id(), s2.id(), 50));
    book.gradeStudent(CourseScore(c2.id(), s3.id(), 60));

    avg = book.getCourseAverage(c2.id());
    if (avg.has_value())
        cout << avg.value() << endl;
    else
        cout << "no scores recorded for this course" << endl;
    cout << book.getAllAverages() << endl;

    auto average = book.getStudentAverage(c3.id());
    if (average.has_value())
        cout << *average << endl;
    else
        cout << "Average is undefined" << endl;

    // cout << average.value_or(-100) << endl; // optional 

    
    return 0;
}