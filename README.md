TechSoC-PS1-task-2-
 It might be possible that some edge cases are not handled properly.(tried my best to handle every edge case)
 The files studentDetails.csv & adminDetails.csv need to be uploaded in the same directory as the mainPrg.cpp file
  ---> Password for student - At the time of registration, his own roll number. After registration, if student changes his password , then only the new password will be valid         for signin process.(password details can be seen in studentDetails.csv file in current password column)
  ---> Password for admins - (Initials of their name(input by them))*(Institute ID) . For example- If admin enters his name as Sumit Chandra and his institute ID as 101 then          his password will be SC*101. Only this password can be used for signup/signin.
  ---> The studentDetails.csv file stores the details of the students who have already registered. It contains the roll no. and password which have a role in registration             check process and verification of password process. It is necessary for a student to register. Without registering, he won't be able to see his academic record and             change his password. A student cannot register twice using his roll number. Once a student is successfully registered(his details are added in studentDetails.csv file)         , he will be allowed to see the student menu page where he has the option to see his academic record and change his password. His academic record will be shown to him          only when a admin had created his studentProfile(which contains all the grades) before. He can also change his current password and the new password will be updated in         the studentDetails.csv file.
 ---> The adminDetails.csv file stores the details of the admins who have already registered. It contains the instituteID which has a role in registration check process . It         is necessary for a admin to register using his unique institute ID. Without registering, he won't be able to access the admin menu. A admin cannot register twice using         his institute ID. Once a admin is successfully registered(his details are added in adminDetails.csv file) , he will be allowed to see the admin menu page where he has          all the necessary options available.For creating a student's academic record, admin has to create a student profile first and then follow the commands accordingly.
                                                                                                                                                                                    **NOTE**- I have signed up for two admins , they can directly sign in.                                                                                                                    1. Sumit Chandra with institute Id 101 and his password is SC*101                                                                                                               2. Bivas Dutta with institute Id 102 and his password is BD*102                                                                                                                                                                                                                                                                                       **NOTE**- I have signed up for three students , they can directly sign in.                                                                                                                1. Abhinav Patel with roll number 240001004 and his password is Abhinav_Patel                                                                                                   2. Abhay Lodhi with roll number 240001003 and his password as his roll number.     
                  3. Abhishek Raj with roll number 240001006 and his password as his roll number.
    **NOTE**- The academic record files of these three students are uploaded here in the github. So using the respective roll number and password , the respective academic                   record file can be seen(Make sure that the files are uploaded in the same directory as the mainPrg.cpp file)    
