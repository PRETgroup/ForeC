/* thread:main:start */
sw ...
@/* statement:abort:1:scope:start */@
swi ...
@@/* statement:pause:1:start */@@
@@addik ...@@
@@br ...@@
@@/* statement:pause:1:end */@@
@/* statement:abort:1:start */@
@bgei ...@
@bri ...@
@/* statement:abort:1:end */@
@@@/* statement:par:1:tA:tB:start */@@@
@@@swi ...@@@
@@@sw ...@@@
@@@br ...@@@
@@@/* statement:par:1:end */@@@
@/* statement:abort:1:scope:end */@
br ...
/* thread:main:end */
...