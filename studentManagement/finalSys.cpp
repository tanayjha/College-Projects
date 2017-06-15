#include <bits/stdc++.h>
using namespace std;

/*There will be three files
1. Student.txt // Contains data of all Students currently studying.
2. Courses.txt // Contains Courses of all Section, Branch, Semester.
3. ArchiveStudent
*/

/*  STUDENT HANDLER  */
class Student{
public:
	string rollno;  // format, unique
	string fname; // first name only string.
	string lname; // last name only string
	char sex;	// M/F
	string section; // UG/PG
	string dob;	// dd/mm/yyyy age for ug>=17 && age <= 19 for pg >= 24 && pg <= 26
	string branch; //COE/ECE/ME/ICE/BT/IT/MPAE - UG, COE/ECE/IT - PG.
	string address;	
	string phno; // format 10 digit
	string date_of_enrollment;	// for archive table constraint not in future
	int semester; // UG- 8, PG- 2
	void addStudent();	// check constraints	
	void editStudent();	// check constraints
	void deleteStudent(); // push in archive
	void viewStudentBySection();	// print details
	void viewStudentByBranch();
	void viewStudentBySem();
	void putStudent();	//list out roll no of vectors Students
	// If roll no not present in current sem, return details by searching in archive else return not present
};
vector<Student> Students, ArcStu;
// for minimizing file access, inserting complete file in a vector
void getStudent(){
	Students.clear();
	ifstream sfile;
    sfile.open("students.txt", ios::in);
    if(!sfile.is_open()){
    	return;
    }
    while(!sfile.eof()){
		Student s;
    	sfile >> s.rollno;
    	if(s.rollno == ""){
    		break;
    	}
    	sfile >> s.fname >> s.lname >> s.dob >> s.phno >> s.sex >> s.address >> s.section >> s.branch >> s.date_of_enrollment >> s.semester;
    	Students.push_back(s);
    }
    return;
}

void getArchiveStudent(){
	ArcStu.clear();
	ifstream sfile;
    sfile.open("ArchiveStudent.txt", ios::in);
    if(!sfile.is_open()){
    	return;
    }
    while(!sfile.eof()){
		Student s;
    	sfile >> s.rollno;
    	if(s.rollno == ""){
    		break;
    	}
    	sfile >> s.fname >> s.lname >> s.dob >> s.phno >> s.sex >> s.address >> s.section >> s.branch >> s.date_of_enrollment >> s.semester;
    	ArcStu.push_back(s);
    }
    return;
}

/*  CLASS HANDLER  */
class Course{
public:
	string course_id;	// unique
	string name;
	string type;	// core/elective
	int credits;	// >=1 & <= 4
	string section;	// UG/PG
	string branch;	// COE..
	int semester;	// ug(1-8) pg(1-2)
public:
	void getCourse();	// for minimizing file access, inserting complete file in a vector
	void addCourse();	// check constraints
	void editCourse();	// check constraints
	void deleteCourse();	
	void viewCourseBySem();
	void viewCourseByBranch();
	void viewCourseBySection();
	void putCourse();
};
vector <Course> courseVector;
void getCourse(){
	courseVector.clear();
	ifstream course;
	course.open("Courses.txt", ios::in);
	if(!course.is_open())
		return;
	while(!course.eof()){
		Course co;
		course>>co.course_id;
		if(co.course_id == "")
			break;
		course>>co.name;
		course>>co.credits;
		course>>co.section;
		course>>co.branch;
		course>>co.semester;
		course>>co.type;
		courseVector.push_back(co);
	}
}

bool uniqueRollNo(string r){
	Students.clear();
	getStudent();
	if(r == ""){
		return false;
	}
	vector<Student>::iterator it;
    for (it = Students.begin(); it != Students.end(); ++it) {
        if(it->rollno == r){
        	return false;
        }
    }
    return true;
}
bool formatRollNo(string a){
	if(a == ""){
		return false;
	}
	if(!(a.length() == 9)){
		return false;
	}
	int year2 = (a[8]-'0') + (a[7]-'0')*10;
	time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int curryear = now->tm_year + 1900;
    int x = curryear%100;
    if(year2 > x)
    	return false;
	for(int i = 0; i < a.length(); i++){
		if(i == 0 || i == 1 || i == 2){
			if(a[i] <= '9' && a[i] >= '0');
			else return false;
		} 
		else if(i == 3 || i == 6){
			if(a[i] == '/');
			else return false;
		}
		else if(i == 4 || i == 5){ 
			if((a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= 'a' && a[i] <= 'z'));
			else return false;
		}
		else if(i == 7 || i == 8){
			if(a[i] <= '9' && a[i] >= '0');
			else return false;
		}
	}
	return true;
}
void putStudent(){
	getStudent();
	getArchiveStudent();
	string rno;
	xyz:
	cout << "Enter the Roll No of students whose details you want to see - Format(051/CO/13) : ";
	cin >> rno;
	if(!(formatRollNo(rno))){
		cout << "Enter in correct format, enter again\n";
		goto xyz;
	}
	cout << "Roll No\t\tFirst Name\tLast Name\tDate Of Birth\t Phone Number\tSex\tAddress\t\tSection\t\tBranch\tYearOfEnrollment\tSemester\tIsStudentActive\n";
	vector<Student>::iterator it;
    for(it = Students.begin(); it != Students.end(); ++it) {
    	if(it->rollno == rno){
    		cout << it->rollno << "\t" << it->fname << "\t\t" << it->lname << "\t\t" << it->dob << "\t" <<  it->phno << "\t" << it->sex << "\t" <<  it->address << "\t\t" <<  it->section << "\t\t" <<  it->branch << "\t\t" <<  it->date_of_enrollment << "\t\t" <<  it->semester << "\t\t" <<  "YES" <<endl;
    	}
    }
	for(it = ArcStu.begin(); it != ArcStu.end(); ++it) {
    	if(it->rollno == rno){
    		cout << it->rollno << "\t" << it->fname << "\t\t" << it->lname << "\t\t" << it->dob << "\t" <<  it->phno << "\t" << it->sex << "\t" <<  it->address << "\t\t" <<  it->section << "\t\t" <<  it->branch << "\t\t" <<  it->date_of_enrollment << "\t\t" <<  it->semester << "\t\t" <<  "NO" <<endl;
    	}
    } 
}
bool formatName(string n){
	if(n == ""){
		return false;
	}
	for(int i = 0; i < n.length(); i++){
		if((n[i] <= 'z' && n[i] >= 'a') || (n[i] >= 'A' && n[i] <= 'Z'));
		else{
			return false;
		}
	}
	return true;
}
bool formatSection(string s){
	if(s == ""){
		return false;
	}
	if(!(s.compare("UG")) || !(s.compare("PG"))){
		return true;
	}
	return false;
}
int stoi(string a){
	int num = (int)(a[0]-'0');
	for(int i = 1; i < a.length(); i++){
		num = num*10 + (int)(a[i]-'0');
	}
	return num;
}
bool formatDOBUG(string a){
	if(!(a.length() == 10)){
		return false;
	}
	if(a[2] != '/' || a[5] != '/')
		return false;
	if((a[1]-'0') + (a[0]-'0')*10 > 31 || (a[4]-'0') + (a[3]-'0')*10 > 12)
		return false;
	int year2 = (a[9]-'0') + (a[8]-'0')*10 + (a[7]-'0')*100 + (a[6]-'0')*1000;
	time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int curryear = now->tm_year + 1900;
	if(curryear-year2  >= 17 && curryear-year2 <= 22);
	else{
		return false;
	}
	return true;
}
bool formatDOBPG(string a){
	if(!(a.length() == 10)){
		return false;
	}
	if(a[2] != '/' || a[5] != '/')
		return false;
	if((a[1]-'0') + (a[0]-'0')*10 > 31 || (a[4]-'0') + (a[3]-'0')*10 > 12)
		return false;
	int year2 = (a[9]-'0') + (a[8]-'0')*10 + (a[7]-'0')*100 + (a[6]-'0')*1000;
	time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int curryear = now->tm_year + 1900;
	if(curryear-year2  >= 21 && curryear-year2 <= 25);
	else{
		return false;
	}
	return true;
}
bool formatBranchUG(string b){
	vector<string> branches;
	branches.push_back("COE");
	branches.push_back("ECE");
	branches.push_back("IT");
	branches.push_back("MPAE");
	branches.push_back("BT");
	branches.push_back("ICE");
	vector<string>::iterator it;
    for (it = branches.begin(); it != branches.end(); ++it) {
        if(!((*it).compare(b))){
	    	return true;
        }
    }
    return false;
}
bool formatBranchPG(string b){
	vector<string> branches;
	branches.push_back("COE");
	branches.push_back("ECE");
	branches.push_back("IT");
	branches.push_back("MPAE");
	branches.push_back("BT");
	branches.push_back("ICE");
	vector<string>::iterator it;
    for (it = branches.begin(); it != branches.end(); ++it) {
        if(!((*it).compare(b))){
	    	return true;
        }
    }
    return false;
}
bool formatPhNo(string a){
	if(!(a.length() == 10)){
		return false;
	}
	for(int i = 0; i < a.length(); i++){
		if(a[i] >= '0' && a[i] <= '9');
		else return false;
	}
	return true;
}
bool formatYOE(string a){
	if(!(a.length() == 4)){
		return false;
	}
	for(int i = 0; i < a.length(); i++){
		if(a[i] >= '0' && a[i] <= '9');
		else return false;	
	}
	return true;
}
bool checkPrevSem(int sem, string roll){
	ArcStu.clear();
	getArchiveStudent();
	Students.clear();
	getStudent();
	if(sem == 1)
		return true;
	vector<Student>::iterator it;
    for (it = Students.begin(); it != Students.end(); ++it) {
        if(it->rollno == roll && it->semester == sem-1){
        	return true;
        }
    }
    for (it = ArcStu.begin(); it != ArcStu.end(); ++it) {
        if(it->rollno == roll && it->semester == sem-1){
        	return true;
        }
    }
    return false;
}
void addStudent(int isEdit, string rno){
	getStudent();
	getCourse();
	Student s;
	ofstream sfile, sissue;
	sfile.open("students.txt", ios::app);
	if(!isEdit){
		enterrollno:
		cout << "Enter Student's Roll No - Format(111/CO/13) : ";
		cin >> s.rollno;
		if(!(uniqueRollNo(s.rollno)) || !(formatRollNo(s.rollno))){
			cout << "Entered Roll No is not Unique or is of wrong format, enter again\n";
			goto enterrollno;
		}
	}
	else{
		s.rollno = rno;
	}
	enterfirstname:
	cout << "Enter First Name of the Student: ";
	cin >> s.fname;
	if(!formatName(s.fname)){
		cout << "Name can be string only, enter again\n";
		goto enterfirstname;
	}
	enterlastname:
	cout << "Enter Last Name of the Student: ";
	cin >> s.lname;
	if(!formatName(s.lname)){
		cout << "Name can be string only, enter again\n";
		goto enterlastname;
	}
	entersection:
	cout << "Enter Section of the Student - (UG/PG): ";
	cin >> s.section;
	if(!formatSection(s.section)){
		cout << "Section can be PG or UG only, enter again\n";
		goto entersection;
	}
	enterdob:
	if(!(s.section.compare("UG"))){
		cout << "Enter Date of Birth for UG student (17 <= age <= 22) - Format(dd/mm/yyy) : ";
		cin >> s.dob;
		if(!formatDOBUG(s.dob)){
			cout << "Entered DOB is not in correct format, enter again\n";
			goto enterdob;
		}
	}
	else if(!(s.section.compare("PG"))){
		cout << "Enter Date of Birth for PG student (21 <= age <= 25)- Format(dd/mm/yyy) : ";
		cin >> s.dob;
		if(!formatDOBPG(s.dob)){
			cout << "Entered DOB is not in correct format, enter again\n";
			goto enterdob;
		}
	}
	enterbranch:
	if(!(s.section.compare("UG"))){
		cout << "Enter Branch - (COE/ECE/ICE/MPAE/IT/BT): ";
		cin >> s.branch;
		if(!formatBranchUG(s.branch)){
			cout << "Enter correct branch, enter again\n";
			goto enterbranch;
		}
	}
	else if(!(s.section.compare("PG"))){
		cout << "Enter Branch - (COE/ECE/ICE/MPAE/IT/BT): ";
		cin >> s.branch;
		if(!formatBranchPG(s.branch)){
			cout << "Enter correct branch, enter again\n";
			goto enterbranch;
		}
	}
	cout << "Enter Address: ";
	cin >> s.address;
	enterphno:
	cout << "Enter 10 Digit Phone Number: ";
	cin >> s.phno;
	if(!formatPhNo(s.phno)){
		cout << "Enter in correct format, enter again\n";
		goto enterphno;
	}
	enteryoe:
	cout << "Enter Year of Enrollment: ";
	cin >> s.date_of_enrollment;
	if(!formatYOE(s.date_of_enrollment)){
		cout << "Enter in correct format, enter again\n";
		goto enteryoe;
	}
	entersem:
	if(!(s.section.compare("UG"))){
		cout << "Enter Semester for UG Student (1-8): ";
		cin >> s.semester;
		if(!(s.semester >= 1 && s.semester < 9)){
			cout << "Enter in correct format, enter again\n";
			goto entersem;
		}
	}
	else if(!(s.section.compare("PG"))){
		cout << "Enter Semester for PG Student (1-2): ";
		cin >> s.semester;
		if(!(s.semester >= 1 && s.semester <= 2)){
			cout << "Enter in correct format, enter again\n";
			goto entersem;
		}
	}

	if(!checkPrevSem(s.semester, s.rollno)){
		cout<<"The student has not been enrolled in semester "<<s.semester-1<<endl;
		goto entersem;
	}
	entersex:
	cout << "Enter Sex of Student - (M/F): ";
	cin >> s.sex;
	if(!(s.sex == 'M' || s.sex == 'F')){
		cout << "Enter in correct format, enter again\n";
		goto entersex;
	}
	sissue.open("issue.txt", ios::app);
	vector <string> selectedCourse, electiveCourses;
	for(int i = 0; i < courseVector.size(); i++){
		if(courseVector[i].semester == s.semester && courseVector[i].type == "core" && courseVector[i].section == s.section)
			selectedCourse.push_back(courseVector[i].course_id);
		else if(courseVector[i].semester == s.semester && courseVector[i].type == "elective" && courseVector[i].section == s.section)
			electiveCourses.push_back(courseVector[i].course_id);
	}
	cout<<selectedCourse.size()<<endl;
	if(electiveCourses.size()  == 1)
		selectedCourse.push_back(electiveCourses[0]);
	if(electiveCourses.size() > 1){
		selectelective:
		int choice;
		cout<<"Choose one course out of the following elective courses:\n";
		for(int i = 0; i < electiveCourses.size(); i++){
			cout<<i+1<<". "<<electiveCourses[i]<<endl;
		}
		cin>>choice;
		int f = 0;
		if(choice >= 1 && choice <= electiveCourses.size())
			f = 1;
		if(!f)
			goto selectelective;
		else{
			selectedCourse.push_back(electiveCourses[choice-1]);
		}
	}
	sissue << s.rollno<<" "<< selectedCourse.size()<<" ";
	for(int i = 0; i < selectedCourse.size(); i++){
		sissue<<selectedCourse[i]<<" ";
	}
	sissue <<endl;
	sfile << s.rollno << " " << s.fname << " " << s.lname << " " << s.dob << " " <<  s.phno << " " << s.sex << " " <<  s.address << " " <<  s.section << " " <<  s.branch << " " <<  s.date_of_enrollment << " " <<  s.semester << endl;
	if(!isEdit){
		cout << "Student Added\n";
	}
	else{
		cout << "Student Edited\n";
	}
	sfile.close();
	sissue.close();
}
void editStudent(){
	string rno;
	int i = 0;
	getStudent();
	edStu: cout << "Enter Roll No of Student whose info you want to edit : ";
	cin >> rno;
	vector<Student>::iterator it2;
    for (it2 = Students.begin(); it2 != Students.end(); ++it2) {
    	if(it2->rollno == rno){
    		i = 1;
    		break;
    	}
    }
    if(!i){
    	cout << "This Student does not exist\n";
    	goto edStu;
    }
    ofstream sfile2;
    sfile2.open("temp.txt", ios::app);
    vector<Student>::iterator it;
    for(it = Students.begin(); it != Students.end(); ++it) {
    	if(it->rollno != rno){
    		sfile2 << it->rollno << " " << it->fname << " " << it->lname << " " << it->dob << " " <<  it->phno << " " << it->sex << " " <<  it->address << " " <<  it->section << " " <<  it->branch << " " <<  it->date_of_enrollment << " " <<  it->semester << endl;
    	}
    }
    remove("students.txt");
    rename("temp.txt", "students.txt");
    addStudent(1,rno);
}
void deleteStudent(){
	string rno;
	int i = 0;
	getStudent();
	delStu: cout << "Enter Roll No of Student to delete: ";
	cin >> rno;
	vector<Student>::iterator it2;
    for (it2 = Students.begin(); it2 != Students.end(); ++it2) {
    	if(it2->rollno == rno){
    		i = 1;
    		break;
    	}
    }
    if(!i){
    	cout << "This Student does not exist\n";
    	goto delStu;
    }
    ofstream sfile2, sfileArc, sissue1;
    ifstream sissue;    
    sfile2.open("temp.txt", ios::app);
    sfileArc.open("ArchiveStudent.txt", ios::app);
    vector<Student>::iterator it;
    for(it = Students.begin(); it != Students.end(); ++it) {
    	if(it->rollno != rno){
    		sfile2 << it->rollno << " " << it->fname << " " << it->lname << " " << it->dob << " " <<  it->phno << " " << it->sex << " " <<  it->address << " " <<  it->section << " " <<  it->branch << " " <<  it->date_of_enrollment << " " <<  it->semester << endl;
    	}
    	else{
    		sfileArc << it->rollno << " " << it->fname << " " << it->lname << " " << it->dob << " " <<  it->phno << " " << it->sex << " " <<  it->address << " " <<  it->section << " " <<  it->branch << " " <<  it->date_of_enrollment << " " <<  it->semester << endl;
    	}
    }
    remove("students.txt");
    rename("temp.txt", "students.txt");
    sissue1.open("temp1.txt", ios::app);
    sissue.open("issue.txt", ios::in);
    if(!sissue.is_open()){
    	return;
    }
    while(!sissue.eof()){
		string roll;
    	sissue >> roll;
    	if(roll == ""){
    		break;
    	}
    	int x;
    	string a;
    	if(roll != rno){
    		sissue1<<roll<<" ";
    		sissue>>x;
    		sissue1<<x<<" ";
    		while(x--){
    			sissue>>a;
    			sissue1<<a<<" ";
    		}
    		sissue1<<endl;
    	}
    	else{
    		sissue>>x;
    		for(int i = 1; i <=x; i++){
    			sissue>>a;
    		}
    	}
    }
    sissue.close();
    remove("issue.txt");
    rename("temp1.txt", "issue.txt");
    cout << "Student Deleted\n";
}
void viewStudentBySection(){
	getStudent();
	getArchiveStudent();
	string sec;
	xyz:
	cout << "Enter the section whose students you want to see (UG/PG) ? : ";
	cin >> sec;
	if(!(formatSection(sec))){
		cout << "Enter in correct format, enter again\n";
		goto xyz;
	}
	cout << "Roll No\t\tFirst Name\tLast Name\tDate Of Birth\t Phone Number\tSex\tAddress\t\tSection\t\tBranch\tYearOfEnrollment\tSemester\tIsStudentActive\n";
	vector<Student>::iterator it;
    for(it = Students.begin(); it != Students.end(); ++it) {
    	if(it->section == sec){
    		cout << it->rollno << "\t" << it->fname << "\t\t" << it->lname << "\t\t" << it->dob << "\t" <<  it->phno << "\t" << it->sex << "\t" <<  it->address << "\t\t" <<  it->section << "\t\t" <<  it->branch << "\t\t" <<  it->date_of_enrollment << "\t\t" <<  it->semester << "\t\t" <<  "YES" <<endl;
    	}
    }
	for(it = ArcStu.begin(); it != ArcStu.end(); ++it) {
    	if(it->section == sec){
    		cout << it->rollno << "\t" << it->fname << "\t\t" << it->lname << "\t\t" << it->dob << "\t" <<  it->phno << "\t" << it->sex << "\t" <<  it->address << "\t\t" <<  it->section << "\t\t" <<  it->branch << "\t\t" <<  it->date_of_enrollment << "\t\t" <<  it->semester << "\t\t" <<  "NO" <<endl;
    	}
    } 
}
void viewStudentByBranch(){
	getStudent();
	getArchiveStudent();
	string bra;
	qwe:
	cout << "Enter the branch whose students you want to see (COE/ECE/MPAE/IT/ICE/BT) ? : ";
	cin >> bra;
	if(!(formatBranchUG(bra))){
		cout << "Enter in correct format, enter again\n";
		goto qwe;
	}
	cout << "Roll No\t\tFirst Name\tLast Name\tDate Of Birth\t Phone Number\tSex\tAddress\t\tSection\t\tBranch\tYearOfEnrollment\tSemester\tIsStudentActive\n";
	vector<Student>::iterator it;
    for(it = Students.begin(); it != Students.end(); ++it) {
    	if(it->branch == bra){
    		cout << it->rollno << "\t" << it->fname << "\t\t" << it->lname << "\t\t" << it->dob << "\t" <<  it->phno << "\t" << it->sex << "\t" <<  it->address << "\t\t" <<  it->section << "\t\t" <<  it->branch << "\t\t" <<  it->date_of_enrollment << "\t\t" <<  it->semester << "\t\t" <<  "YES" <<endl;
    	}
    }
	for(it = ArcStu.begin(); it != ArcStu.end(); ++it) {
    	if(it->branch == bra){
    		cout << it->rollno << "\t" << it->fname << "\t\t" << it->lname << "\t\t" << it->dob << "\t" <<  it->phno << "\t" << it->sex << "\t" <<  it->address << "\t\t" <<  it->section << "\t\t" <<  it->branch << "\t\t" <<  it->date_of_enrollment << "\t\t" <<  it->semester << "\t\t" <<  "NO" <<endl;
    	}
    } 
}
void viewStudentBySem(){
	getStudent();
	getArchiveStudent();
	int sem;
	pqr:
	cout << "Enter the semester whose students you want to see (1-8) : ";
	cin >> sem;
	if(!(sem <= 8 && sem >= 1)){
		cout << "Enter in correct format, enter again\n";
		goto pqr;
	}
	cout << "Roll No\t\tFirst Name\tLast Name\tDate Of Birth\t Phone Number\tSex\tAddress\t\tSection\t\tBranch\tYearOfEnrollment\tSemester\tIsStudentActive\n";
	vector<Student>::iterator it;
    for(it = Students.begin(); it != Students.end(); ++it) {
    	if(it->semester == sem){
    		cout << it->rollno << "\t" << it->fname << "\t\t" << it->lname << "\t\t" << it->dob << "\t" <<  it->phno << "\t" << it->sex << "\t" <<  it->address << "\t\t" <<  it->section << "\t\t" <<  it->branch << "\t\t" <<  it->date_of_enrollment << "\t\t" <<  it->semester << "\t\t" <<  "YES" <<endl;
    	}
    }
	for(it = ArcStu.begin(); it != ArcStu.end(); ++it) {
    	if(it->semester == sem){
    		cout << it->rollno << "\t" << it->fname << "\t\t" << it->lname << "\t\t" << it->dob << "\t" <<  it->phno << "\t" << it->sex << "\t" <<  it->address << "\t\t" <<  it->section << "\t\t" <<  it->branch << "\t\t" <<  it->date_of_enrollment << "\t\t" <<  it->semester << "\t\t" <<  "NO" <<endl;
    	}
    } 
}



void putCourse(){
	getCourse();
	string cid;
	cout<<"Enter the Course ID whose details you want to view ";
	cin >> cid;
	cout<<"The details for " << cid << " Course are:\n";
	cout<<"S.No\tCourse Id\tCourse Name\tCredits\t\tSection\t\tBranch\t\tSemester\tType"<<endl;
	for(int i = 0; i < courseVector.size(); i++){
		if(courseVector[i].course_id == cid){
			cout<<courseVector[i].course_id<<"\t\t"<<courseVector[i].name<<"\t\t"<<courseVector[i].credits<<"\t\t"<<courseVector[i].section<<"\t\t"<<courseVector[i].branch<<"\t\t"<<courseVector[i].semester<<"\t\t"<<courseVector[i].type<<endl;
		}
	}
}
bool isUniqueCourse_id(string a){
	if(a == "")
		return false;
	for(int i = 0; i < courseVector.size(); i++){
		if(courseVector[i].course_id == a){
			return false;
		}
	}
	return true;
}
bool isValidName(string a){
	if(a == "")
		return false;
	return true;
}
bool isValidCredit(int x){
	if(x>=1 && x<= 4)
		return true;
	return false;
}
bool isValidSection(string a){
	if(a == "UG" || a == "PG")
		return true;
	return false;
}
bool isValidBranch(string a){
	if(a == "COE" || a == "IT" || a == "MPAE" || a == "ICE" || a == "BT" || a == "ECE")
		return true;
	return false;
}
bool isValidSemester(int a, string b){
	if(b == "UG"){
		if(a >= 1 && a <= 8)
			return true;
		return false;
	}
	else{
		if(a == 1 || a == 2)
			return true;
		return false;
	}
}
bool isValidType(string a){
	if(a == "core" || a == "elective")
		return true;
	return false;
}
void addCourse(int isEdit, string cid){
	getCourse();
	ofstream course;
	Course co;
	course.open("Courses.txt", ios::app);
	if(!isEdit){
		label1: cout<<"Enter the course_id ";
		cin>>co.course_id;
		if(!isUniqueCourse_id(co.course_id)){
			cout<<"A course with this id already exists!\n";
			goto label1;
		}
	}
	else
		co.course_id = cid;
	label: cout<<"Enter the course name ";
	cin>>co.name;
	if(!isValidName(co.name)){
		cout<<"Enter a non empty name!\n";
		goto label;
	}
	label2: cout<<"Enter the credits of the course ";
	cin>>co.credits;
	if(!isValidCredit(co.credits)){
		cout<<"Enter the correct credit!\n";
		goto label2;
	}
	label3: cout<<"Enter the programme(UG/PG) ";
	cin>>co.section;
	if(!isValidSection(co.section)){
		cout<<"Enter the correct section!\n";
		goto label3;
	}
	label4: cout<<"Enter the branch(COE/ECE/IT/MPAE/BT/ICE) ";
	cin>>co.branch;
	if(!isValidBranch(co.branch)){
		cout<<"Enter the correct branch!\n";
		goto label4;
	}
	label5: cout<<"Enter the semester of the course ";
	cin>>co.semester;
	if(!isValidSemester(co.semester, co.section)){
		cout<<"Enter a valid semester!\n";
		goto label5;
	}
	label6: cout<<"Enter whether the course is core/elective ";
	cin>>co.type;
	if(!isValidType(co.type)){
		cout<<"Enter a valid type!\n";
		goto label6;
	}
	course<<co.course_id<<" "<<co.name<<" "<<co.credits<<" "<<co.section<<" "<<co.branch<<" "<<co.semester<<" "<<co.type<<endl;
	if(!isEdit)
		cout<<"Course Successfully Added!\n";
	else
		cout<<"Course Successfully Edited!\n";

	course.close();
}
void editCourse(){
	string cid;
	int f = 0;
	getCourse();
	cout<<"Enter the course_id which you want to edit ";
	cin>>cid;
	for(int i = 0; i < courseVector.size(); i++){
		if(courseVector[i].course_id == cid){
			f = 1;
			break;
		}
	}
	if(!f){
		cout<<"This course does not exist!";
		return;
	}
	ofstream edCourse;
	edCourse.open("temp.txt", ios::app);
	for(int i = 0; i < courseVector.size(); i++){
		if(courseVector[i].course_id != cid){
			edCourse<<courseVector[i].course_id<<" "<<courseVector[i].name<<" "<<courseVector[i].credits<<" "<<courseVector[i].section<<" "<<courseVector[i].branch<<" "<<courseVector[i].semester<<" "<<courseVector[i].type<<endl;
		}
	}
	remove("Courses.txt");
	rename("temp.txt", "Courses.txt");
	addCourse(1, cid);
}
void deleteCourse(){
	string cid;
	int f = 0;
	getCourse();
	cout<<"Enter the course_id which you want to delete ";
	cin>>cid;
	for(int i = 0; i < courseVector.size(); i++){
		if(courseVector[i].course_id == cid){
			f = 1;
			break;
		}
	}
	if(!f){
		cout<<"This course does not exist!";
		return;
	}
	ifstream sissue;
	sissue.open("issue.txt", ios::in);
	if(!sissue.is_open()){
    	return;
    }
    f = 0;
    while(!sissue.eof()){
		string roll;
    	sissue >> roll;
    	if(roll == ""){
    		break;
    	}
    	int x;
    	string a;
    	sissue>>x;
    	while(x--){
    		sissue>>a;
    		if(a == cid){
    			f = 1;
    			break;
    		}
    	}
    	if(f)
    		break;
    }
    if(f){
    	cout<<"The course has been alloted to a student and cannot be deleted!\n";
    	sissue.close();
    }
    else{
	    sissue.close();
		ofstream edCourse;
		edCourse.open("temp.txt", ios::app);
		for(int i = 0; i < courseVector.size(); i++){
			if(courseVector[i].course_id != cid){
				edCourse<<courseVector[i].course_id<<" "<<courseVector[i].name<<" "<<courseVector[i].credits<<" "<<courseVector[i].section<<" "<<courseVector[i].branch<<" "<<courseVector[i].semester<<" "<<courseVector[i].type<<endl;
			}
		}
		remove("Courses.txt");
		rename("temp.txt", "Courses.txt");
		cout<<"Course Succesfully deleted!\n";
	}
}
void viewCourseBySection(){
	getCourse();
	string sec;
	label6: cout<<"Enter the section whose courses you want to view(UG/PG) ";
	cin>>sec;
	if(!isValidSection(sec)){
		cout<<"Enter the correct section!\n";
		goto label6;
	}
	cout<<"The courses for "<<sec<<" programme are:\n";
	int k = 0;
	cout<<"S.No\tCourse Id\tCourse Name\tCredits\t\tSection\t\tBranch\t\tSemester\tType"<<endl;
	for(int i = 0; i < courseVector.size(); i++){
		if(courseVector[i].section == sec){
			k++;
			cout<<k<<".\t"<<courseVector[i].course_id<<"\t\t"<<courseVector[i].name<<"\t\t"<<courseVector[i].credits<<"\t\t"<<courseVector[i].section<<"\t\t"<<courseVector[i].branch<<"\t\t"<<courseVector[i].semester<<"\t\t"<<courseVector[i].type<<endl;
		}
	}
}
void viewCourseByBranch(){
	getCourse();
	string branch;
	label7: cout<<"Enter the branch whose courses you want to view(COE/ECE/IT/MPAE/BT/ICE) ";
	cin>>branch;
	if(!isValidBranch(branch)){
		cout<<"Enter the correct branch!\n";
		goto label7;
	}
	cout<<"The courses for the branch"<<branch<<" are:\n";
	int k = 0;
	cout<<"S.No\tCourse Id\tCourse Name\tCredits\t\tSection\t\tBranch\t\tSemester\tType"<<endl;
	for(int i = 0; i < courseVector.size(); i++){
		if(courseVector[i].branch == branch){
			k++;
			cout<<k<<".\t"<<courseVector[i].course_id<<"\t\t"<<courseVector[i].name<<"\t\t"<<courseVector[i].credits<<"\t\t"<<courseVector[i].section<<"\t\t"<<courseVector[i].branch<<"\t\t"<<courseVector[i].semester<<"\t\t"<<courseVector[i].type<<endl;
		}
	}
}
void viewCourseBySem(){
	getCourse();
	int sem;
	label8: cout<<"Enter the semester whose courses you want to view(1-8) ";
	cin>>sem;
	if(!isValidSemester(sem, "UG")){
		cout<<"Enter the correct semester!\n";
		goto label8;
	}
	cout<<"The courses for the semester "<<sem<<" are:\n";
	int k = 0;
	cout<<"S.No\tCourse Id\tCourse Name\tCredits\t\tSection\t\tBranch\t\tSemester\tType"<<endl;
	for(int i = 0; i < courseVector.size(); i++){
		if(courseVector[i].semester == sem){
			k++;
			cout<<k<<".\t"<<courseVector[i].course_id<<"\t\t"<<courseVector[i].name<<"\t\t"<<courseVector[i].credits<<"\t\t"<<courseVector[i].section<<"\t\t"<<courseVector[i].branch<<"\t\t"<<courseVector[i].semester<<"\t\t"<<courseVector[i].type<<endl;
		}
	}
}

void listCourses(){
	getStudent();
	getCourse();
	string rollNo;
	enterroll:
	cout << "Enter the roll no. of the student whose courses you want to see: ";
	cin >> rollNo;
	if(!(formatRollNo(rollNo))){
		cout << "Entered Roll No is of wrong format, enter again\n";
		goto enterroll;
	}
	int sem = 0;
	string sec, bra;
	vector<Student>::iterator it;
	vector<Course>::iterator it1;
    for(it = Students.begin(); it != Students.end(); ++it) {
    	if(it->rollno == rollNo){
    		sem = it->semester;
    		bra = it->branch;
    		sec = it->section;
    		break;
    	}
    }
    int k = 0;
    if(!sem){
    	cout<<"The student does not exist!\n";
    	return;
    }
    else{
    	ifstream sissue;
    	sissue.open("issue.txt", ios::in);
    	if(!sissue.is_open()){
    		return;
    	}
	    while(!sissue.eof()){
			string roll;
	    	sissue >> roll;
	    	if(roll == ""){
	    		break;
	    	}
	    	int x;
	    	string a;
	    	if(roll != rollNo){
	    		sissue>>x;
	    		while(x--){
	    			sissue>>a;
	    		}
	    	}
	    	else{
	    		k = 1;
	    		sissue>>x;
	    		cout<<"The student is enrolled in the following courses\n";
	    		for(int i = 1; i <=x; i++){
	    			sissue>>a;
	    			cout<<i<<". "<<a<<endl;
	    		}
	    		break;	
	    	}
	    }
	    sissue.close();
    }
    if(k == 0)
    	cout<<"There are no courses assigned for the semester in which the student is enrolled!\n";
}
bool checkMigration(string a){
	time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    int curryear = now->tm_year + 1900;
    int curmon = now->tm_mon + 1;
    int year2 = (a[3]-'0') + (a[2]-'0')*10 + (a[1]-'0')*100 + (a[0]-'0')*1000;
    if(year2 < 2013)
    	return true;
    return false;
    /*int mon2 = stoi(a.substr(2,2));
    if(curryear == year2){
    	if(abs(curmon-mon2) >= 6)
    		return true;
    	else
    		return false;
    }
    else if(curryear>year2)
    	return true;
    return false;*/
}
void migrateDatabase(){
	getStudent();
    vector<Student>::iterator it;
    ofstream sfile2, sfileArc;
    sfile2.open("temp.txt", ios::app);
    sfileArc.open("ArchiveStudent.txt", ios::app);
	for(it = Students.begin(); it != Students.end(); ++it) {
    	if(checkMigration(it->date_of_enrollment)){    
    		cout<<"Here";	
		    sfileArc << it->rollno << " " << it->fname << " " << it->lname << " " << it->dob << " " <<  it->phno << " " << it->sex << " " <<  it->address << " " <<  it->section << " " <<  it->branch << " " <<  it->date_of_enrollment << " " <<  it->semester << endl;
		}
		else{
    		sfile2 << it->rollno << " " << it->fname << " " << it->lname << " " << it->dob << " " <<  it->phno << " " << it->sex << " " <<  it->address << " " <<  it->section << " " <<  it->branch << " " <<  it->date_of_enrollment << " " <<  it->semester << endl;
		}
    }
    remove("students.txt");
    rename("temp.txt", "students.txt");
}
int main()
{
	migrateDatabase();
    int n, ch1, ch2;
    while(1){
    	cout<<"\t\t**********************************************\n";
        cout<<"\t\t*  Welcome to the student management system  *"<<endl;
        cout<<"\t\t**********************************************\n";
        cout<<"Press 1 to manage a student"<<endl;
        cout<<"Press 2 to manage a Course"<<endl;
        cout<<"Enter your choice ";
        cin>>ch1;
        switch(ch1){
        	case 1:
        		cout<<"Press 1 to add a new Student"<<endl;
		        cout<<"Press 2 to edit a Student"<<endl;
		        cout<<"Press 3 to delete a Student"<<endl;
		        cout<<"Press 4 to view Student by Section"<<endl;
		        cout<<"Press 5 to view Student by Branch"<<endl;
		        cout<<"Press 6 to view Student by Semester"<<endl;
		        cout<<"Press 7 to list the courses for which the student has been enrolled for "<<endl;
		        cout<<"Press 8 to view Student Details: "<<endl;
		        cout<<"Enter your choice ";
		        cin>>ch2;
		        switch(ch2){
			        case 1:
		                addStudent(0, "");
		                break;
		            case 2:
		            	editStudent();
		            	break;
		            case 3:
		            	deleteStudent();
		            	break;
		            case 4:
		            	viewStudentBySection();
		            	break;
		            case 5:
		            	viewStudentByBranch();
		            	break;
		            case 6:
		            	viewStudentBySem();
		            	break;
		            case 7:
		            	listCourses();
		            	break;
		            case 8:
		            	putStudent();
		            	break;
		            default:
		                cout<<"Enter valid input!!"<<endl;

		        }
		        break;
		    case 2:
		        cout<<"Press 1 to add a Course"<<endl;		    
		        cout<<"Press 2 to edit a Course"<<endl;
		        cout<<"Press 3 to delete a Course"<<endl;
		        cout<<"Press 4 to view course by Section"<<endl;
		        cout<<"Press 5 to view course by Branch"<<endl;
		        cout<<"Press 6 to view course by Semester"<<endl;
		        cout<<"Press 7 to view Course Details"<<endl;
		        cout<<"Enter your choice ";
		        cin>>ch2;
		        switch(ch2){
		            case 1:
		                addCourse(0, "");
		                break;
		            case 2:
		            	editCourse();
		            	break;
		            case 3:
		            	deleteCourse();
		            	break;
		            case 4:
		            	viewCourseBySection();
		            	break;
		            case 5:
		            	viewCourseByBranch();
		            	break;
		            case 6:
		            	viewCourseBySem();
		            	break;
		            case 7:
		            	putCourse();
		            	break;
		            default:
		                cout<<"Enter valid input!!"<<endl;
	        	}
        }
        cout<<"Do you want to continue?(1/0)"<<endl;
        cin>>n;
        if(!n)
            break;
    }
}
