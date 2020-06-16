#/usr/bin/bash

bin/simulator > resource/result.txt

if [[ $(cat resource/result.txt | grep -e" <1> " | wc -l) = 5 ]]; then
	echo PASSED, WAITING STUDENT 1
fi

if [[ $(cat resource/result.txt | grep -e" <<1>> " | wc -l) = 5 ]]; then
	echo PASSED, HELPING STUDENT 1
fi

if [[ $(cat resource/result.txt | grep -e" <<<1>>> " | wc -l) = 5 ]]; then
	echo PASSED, GETTING HELP STUDENT 1
fi

if [[ $(cat resource/result.txt | grep -e" <2> " | wc -l) = 5 ]]; then
	echo PASSED, WAITING STUDENT 2
fi

if [[ $(cat resource/result.txt | grep -e" <<2>> " | wc -l) = 5 ]]; then
	echo PASSED, HELPING STUDENT 2
fi

if [[ $(cat resource/result.txt | grep -e" <<<2>>> " | wc -l) = 5 ]]; then
	echo PASSED, GETTING HELP STUDENT 2
fi

if [[ $(cat resource/result.txt | grep -e" <3> " | wc -l) = 5 ]]; then
	echo PASSED, WAITING STUDENT 3
fi

if [[ $(cat resource/result.txt | grep -e" <<3>> " | wc -l) = 5 ]]; then
	echo PASSED, HELPING STUDENT 3
fi

if [[ $(cat resource/result.txt | grep -e" <<<3>>> " | wc -l) = 5 ]]; then
	echo PASSED, GETTING HELP STUDENT 3
fi

