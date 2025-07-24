# Save this as: generate-hash.ps1
$exePath = "Crackme3.exe"
$hashFilePath = "$exePath.sha256"

$hash = Get-FileHash -Algorithm SHA256 -Path $exePath
$hash.Hash | Out-File -Encoding ascii -NoNewline $hashFilePath
