$tests = @(
	"3`n20`n50`n101",
	"0",
	"2`n-51`n101",
	"2`n0`n40",
	"2`n-50`n100",
	"11",
	"5`n5`n5`ne"
)

$appPath = Join-Path $PSScriptRoot "build\Debug\app.exe"
foreach ($test in $tests) {
    $cleanTest = $test -replace '\r?\n', "`e[32m↵`e[0m"
    Write-Host "`n----- Входные данные: $cleanTest -----"
    $test | & $appPath
    Write-Host "`n--------------------"
}
