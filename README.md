# scd 

**A scheduling application implementation primarily through C - Work in Progress**

NOTES:

1. There is no error checking for the 'add' commands, for now make sure your command is formatted correctly. This will be handled soon. 
2. Deletion is not available yet.  
3. There are five types of schedule items:
   \
   3.1 -primary, p- are the weekly repeating events (e.g. every sunday such and such event takes place) \
   3.2 -day, d- are the events attributed to one specific day (e.g. on the 29th of March 2024 I must attend such and such event) \
   3.3 -week, w- are weekly items, respnsibilities that span an entire week - weeks are defined by the nearest sunday, this is important \
   3.4 -month, m- are monthly items, spans a month      \
   3.5 -special, s- are commitments with user-defined start and end dates (e.g. between the 4th of January 2024 and the 9th of May 2024 I must tend to such and such commitment)

4. Schedule items can contain the follow fields + format     <br>
   4.1 name: max 37 characters     <br>
   4.2 block: 01-48, duration in number of consecutive 30-second blocks, applicable only to primary and day items (e.g. block = 03 means an event takes 90 minutes)    <br>
   4.3 time: 00:00-23:59, military time (e.g. 07:05 or 17:05)    <br>
   4.4 day_of_week: 0-6, where 0 represents Sunday, applicable only to primary items <br>
   4.5 mode: 00-63, no definite functionality other than cool colours. Leave at 0 for most things. <br>
   4.6 day: 00-31 <br>
   4.7 month: 01-12 <br> 
   4.8 year: 0000-9999 <br>
   4.9 day_s, month_s, year_s: starting date (observes same format as 4.6 - 4.8), inclusive, applicable only to special items <br>
   4.10 day_e, month_e, year_e: ending date (observes same format as 4.6 - 4.8), inclusive, applicable only to special items <br>
   <br>
   Really important to observe the exact format when using 'add' command.

5. Using 'add' command <br> 
   5.1 add p <day_of_week> <block_> <time_> <mode_> <name_> <br> 
   5.2 add d <block_> <time_> <day_> <month_> <year_> <mode_> <name_> <br> 
   5.3 add w <day_> <month_> <year_> <mode_> <name_> REMEMBER THIS DATE MUST BE A SUNDAY <br> 
   5.4 add m <month_> <year_> <mode_> <name_> <br> 
   5.5 add s <day_s> <month_s> <year_s> <day_e> <month_e> <year_e> <mode> <name>  <br> 
   



   

    
   



   

