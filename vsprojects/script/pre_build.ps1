Function Get-Webclient ($url, $out) {
  $proxy = [System.Net.WebRequest]::GetSystemWebProxy()
  $proxy.Credentials = [System.Net.CredentialCache]::DefaultCredentials
  $request = New-Object System.Net.WebCLient
  $request.UseDefaultCredentials = $true ## Proxy credentials only
  $request.Proxy.Credentials = $request.Credentials
  $request.DownloadFile($url, $out)
}

mkdir tools -Force > $null

if (!(Test-Path -Path ".\tools\protoc.exe")) {
  mkdir tmp -Force > $null
  echo "Downloading protoc"
  Get-Webclient "https://protobuf.googlecode.com/files/protoc-2.5.0-win32.zip" ".\tmp\protoc-2.5.0-win32.zip"
  echo "Extracting protoc"
  $shell = New-Object -ComObject Shell.Application
  $shell.namespace("$PWD\tmp").copyhere(($shell.namespace("$PWD\tmp\protoc-2.5.0-win32.zip")).items())
  move tmp\protoc.exe tools\
  mkdir empty -FORCE > $null
  robocopy empty tmp /MIR > $null
  rmdir empty
  rmdir tmp
}

if (!(Test-Path -Path ".\tools\7za.exe")) {
  mkdir tmp -Force > $null
  echo "Downloading 7zip"
  Get-Webclient "http://sourceforge.net/projects/sevenzip/files/7-Zip/9.20/7za920.zip/download" ".\tmp\7za920.zip"
  echo "Extracting 7zip"
  $shell = New-Object -ComObject Shell.Application
  $shell.namespace("$PWD\tmp").copyhere(($shell.namespace("$PWD\tmp\7za920.zip")).items())
  move tmp\7za.exe tools\
  mkdir empty -FORCE > $null
  robocopy empty tmp /MIR > $null
  rmdir empty
  rmdir tmp
}

cd ..\src
..\vsprojects\tools\protoc.exe --cpp_out=.\ common\proto\udpgame.proto
