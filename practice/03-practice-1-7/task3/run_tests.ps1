$tests = @(
	"200`n70`n50`n100`n0"
)

$appPath = Join-Path $PSScriptRoot "build\Debug\app.exe"
foreach ($test in $tests) {
    $cleanTest = $test -replace '\r?\n', "`e[32m↵`e[0m"
    Write-Host "`n----- Входные данные: $cleanTest -----"
    $test | & $appPath
    Write-Host "`n--------------------"
}
