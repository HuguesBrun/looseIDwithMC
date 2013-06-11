#!/bin/csh


set suffix="test"
set listDir = {"SFplots","effPlots"}

foreach i ($listDir)
    set listFiles = `ls $i/*.pdf`
    foreach j ($listFiles)
        echo $j
        set newName = `echo $j | awk -F "." '{print $1}'`
        echo $newName
        mv $j ${newName}_${suffix}.pdf
    end
end


