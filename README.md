# scd 

**A scheduling application implementation primarily through C - Work in Progress**

1. Use 'today' to view today's schedule

2. There are five types of schedule items:
   \
   2.1 -primary, p- are the weekly repeating events (e.g. every sunday such and such event takes place) \
   2.2 -day, d- are the events attributed to one specific day (e.g. on the 29th of March 2024 I must attend such and such event) \
   2.3 -week, w- are weekly items, respnsibilities that span an entire week - weeks are defined by the nearest sunday, this is important \
   2.4 -month, m- are monthly items, spans a month      \
   2.5 -special, s- are commitments with user-defined start and end dates (e.g. between the 4th of January 2024 and the 9th of May 2024 I must tend to such and such commitment)

3. Schedule items can contain the follow fields (including format)     <br>
   3.1 name: max 37 characters     <br>
   3.2 block: 01-48 <br>
   -- duration in number of consecutive 30-second blocks, (e.g. block = 03 -> event is 90 mins)    <br>
   3.3 time: 00:00-23:59 <br>
   -- military time (e.g. 07:05 or 17:05)    <br>
   3.4 day_of_week: 0-6 <br>
   -- where 0 represents Sunday, applicable only to primary items <br>
   3.5 mode: 00-63 <br>
   -- leave at 0 for most things, no definite functionality other than cool colours, will be useful later <br>
   3.6 day: 00-31 <br>
   3.7 month: 01-12 <br> 
   3.8 year: 0000-9999 <br>
   3.9 day_s, month_s, year_s: (observes same format as 4.6 - 4.8) <br>
   -- starting date, inclusive, applicable only to special items <br>
   3.10 day_e, month_e, year_e: (observes same format as 4.6 - 4.8) <br>
   -- ending date, inclusive, applicable only to special items <br>
   <br>
   Really important to observe the exact format when using 'add' command.

4. Using 'add' command <br> 
   4.1 add p <day_of_week> <block_> <time_> <mode_> <name_> <br> 
   4.2 add d <block_> <time_> <day_> <month_> <year_> <mode_> <name_> <br> 
   4.3 add w <day_> <month_> <year_> <mode_> <name_> REMEMBER THIS DATE MUST BE A SUNDAY <br> 
   4.4 add m <month_> <year_> <mode_> <name_> <br> 
   4.5 add s <day_s> <month_s> <year_s> <day_e> <month_e> <year_e> <mode_> <name_>  <br> 

   For example <br><br>
   add p 1 02 07:00 00 Event A <br>
   (Every monday, for 60 minutes, starting at 7:00 AM, mode 0 (ignore this), do Event A) <br><br>
   add d 01 20:00 17 02 2024 00 Event B <br>
   (On the 17th of February 2024, for 30 minutes, starting at 8:00 PM, mode 0 (ignore this), do Event B) <br><br>
   add w 11 02 2024 01 Commitment A <br>
   (For the week defined by its sunday on the 11th of February 2024, mode 1 (ignore this), you have Commitment A) <br><br>
   add m 03 2024 00 Commitment B  <br>
   (For March 2024, mode 0 (ignore this), you have Commitment B) <br><br>
   add s 03 02 2024 05 04 2024 00 Commitment C <br>
   (Between February 3rd 2024 and April 5th 2024, mode 0 (ignore this), you have Commitment C) <br><br>

   The items are stored in this format, look at the base files for reference.

5. Using 'delete' command <br>
   5.1 delete p <day_of_week> <time_> <br>
   5.2 delete d <time_> <day_> <month_> <year_> <br>
   5.3 delete w <day_> <month_> <year_> <name_> <br>
   5.4 delete m <month_> <year_> <name_> <br>
   5.5 delete s  <day_s> <month_s> <year_s> <day_e> <month_e> <year_e> <name_> <br> <br>

Notes:
A) Everything after the 'delete x' command is assumed to uniquely identify each schedule item (again, this is not yet enforced, but will in the future) <br>
B) This would also mean that the user is trusted to not 'add' two or more schedule items with the same identifier such as two primary events on Sunday at 15:00 but with different names (also, not yet enforced) <br>
C) There is no error checking for the 'add' and 'delete' commands, for now make sure your command is formatted correctly. (soon to be handled)



   

    
   



   

