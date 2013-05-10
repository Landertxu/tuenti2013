<?
#strcmp returns null when comparing with an array,
#so I send an array as a post value so that
#the comparison between strcmp and null becomes true

$url = 'http://pauth.contest.tuenti.net/';
$data = array('key' => '6fe71372b1599608fe96b452f3adad2116c25266', 'pass' => array('a' => 'b') );

$options = array(
    'http' => array(
        'header'  => "Content-type: application/x-www-form-urlencoded\r\n",
        'method'  => 'POST',
        'content' => http_build_query($data),
    ),
);

$context  = stream_context_create($options);
$result = file_get_contents($url, false, $context);

var_dump($result);
?>