### Трюки

#### Как бороться с предупреждениями в стороннем коде

См.: https://stackoverflow.com/questions/15053776/how-do-you-disable-the-unused-variable-warnings-coming-out-of-gcc-in-3rd-party-c

The `-Wno-unused-variable` switch usually does the trick. However, that is a very useful warning indeed if you care about these things in your project. It becomes annoying when GCC starts to warn you about things not in your code though.

I would recommend you keeping the warning on, but use -isystem instead of -I for include directories of third-party projects. That flag tells GCC not to warn you about the stuff you have no control over.

For example, instead of `-IC:\\boost_1_52_0`, say `-isystem C:\\boost_1_52_0`
