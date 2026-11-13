$tests = @(
	"Test 1`n3 200 1",
	"Test 2`n2 150.5 0",
	"Test 3`n10 5000 1",
	"Test 4`n0 200 1",
	"Test 5`n1 0 1",
	"Test 6`n1 200 2"
)

$appPath = Join-Path $PSScriptRoot "build\Debug\app.exe"
foreach ($test in $tests) {
    $cleanTest = $test -replace '\r?\n', "`e[32m↵`e[0m"
    Write-Host "`n----- Входные данные: $cleanTest -----"
    $test | & $appPath
    Write-Host "`n--------------------"
}
