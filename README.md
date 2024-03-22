# scd (Work in Progress)

**A scheduling application implementation primarily through C.**

NOTES:
1. For the format of base files check the samples in 'base' as references - and edit them as necessary
  1.1 Eventually an interface will handle creation and deletion of schedule items
  1.2 (IMPORTANT) If you add and remove any items, be sure to update the corresponding count value in 'total/count'
  1.3 Anything of the format ::XYZ is a modifier for the previous entry
  1.4 The first two digits in an entry in the 'primary' base is duration in 30 minute time blocks (e.g. 03 is 90 minutes)
   
2. For now you can only view today's items
  2.1 Eventually an interface will handle the viewing of different days

   

